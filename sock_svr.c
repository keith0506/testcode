#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

static void usage(const char* proc)
{ 
    printf("Usage:%s [local_ip] [local_port]\n", proc);
}

int startup(const char* _ip, int _port)
{ 
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    { 
        perror("socket\n");
        exit(2);
    }
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = inet_addr(_ip);
    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
    { 
        perror("bind");
        exit(3);
    }
    if(listen(sock, 10) < 0)
    { 
        perror("listen");
        exit(4);
    }
    return sock;
}

int fds_array[sizeof(fd_set)*8];

int main(int argc, char* argv[])
{ 
    if(argc != 3)
    { 
        usage(argv[1]);
        return 1;
    }
    int listen_sock = startup(argv[1], atoi(argv[2]));
    int num = sizeof(fds_array)/sizeof(fds_array[0]);
    int i = 0;
    for(; i<num; ++i)
    { 
        fds_array[i] = -1;
    }
    fds_array[1] = listen_sock;
    while(1)
    { 
        int maxfd = -1;
        fd_set rfds;
        fd_set wfds;
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        for(i=0; i<num; i++)
        { 
            if(fds_array[i] == -1)
            {    
                continue;
            }

            FD_SET(fds_array[i], &rfds);
            FD_SET(fds_array[i], &wfds);
            if(maxfd < fds_array[i])
            { 
                maxfd = fds_array[i];
            }//更新maxfd
        }

        struct timeval timeout = {5, 0};
        switch( select(maxfd+1,&rfds, &wfds, NULL, NULL) )
        { 
            case -1:
                perror("select");
                break;
            case 0:
                printf("timeout...\n");
                break;
            default:
                { 
                    for(i=0; i<num; i++)
                    {           
    			if(fds_array[i] == -1)                  
                        { 
                            continue;
                        }
                        if(i == 1 && FD_ISSET(fds_array[i], &rfds))//监听到就绪的消息
                        { 
                            struct sockaddr_in client;      
                            int len = sizeof(client);
                            int new_sock = accept(listen_sock,(struct sockaddr*)&client, &len );

                            if(new_sock < 0)
                            { 
                                perror("accept");
                                continue;

                            }
                            printf("get a new client...[%s : %d]\n", inet_ntoa(client.sin_addr),\
                                    ntohs(client.sin_port));

                            int j = 1;
                            for(; j<num; j++)
                            { 
                                if(fds_array[j] == -1)
                                { 
                                    break;
                                }
                            }
                            if(j == num)
                            {
                                printf("fds_array is full!!\n");
                                close(new_sock);
                            }
                            else
                            { 
                                fds_array[j] = new_sock;
                            }
                        }//fi

                        else if(i != 1  && (FD_ISSET(fds_array[i], &rfds) \
                                    || FD_ISSET(fds_array[i], &wfds)))//普通事件就绪    
                        { 
                            char buf[1024];
                            if(FD_ISSET(fds_array[i], &rfds))//读事件就绪
                            { 
                                ssize_t s = read(fds_array[i], buf, sizeof(buf)-1); 

                                if(s > 0)   
                                {
                                    buf[s] = 0;
                                    printf("client# %s\n", buf);
                                    if(FD_ISSET(fds_array[i],&wfds))
                                     { 
                                        printf("please Enter# \n");
                                        fflush(stdout);
                                        ssize_t s = read(0, buf, sizeof(buf)-1);
                                        if(s > 0)
                                        { 
                                            buf[s-1] = 0;
                                            ssize_t s = write(fds_array[i], buf, strlen(buf));
                                            if(s > 0)
                                            {
                                                buf[s] = 0;
                                                printf("server# %s\n", buf);
                                                continue;

                                            }
                                            else if(s == 0)
                                            { 
                                                close(fds_array[i]);
                                                fds_array[i] = -1;
                                                continue;
                                            }

                                            else
                                            { 
                                                perror("write");
                                                close(fds_array[i]);
                                                fds_array[i] = -1;
                                                continue;
                                            }
                                        }
                                        else if(s == 0)
                                        { 
                                            printf("client is quit...\n");
                                            close(fds_array[i]);
                                            fds_array[i] = -1;
                                            continue;
                                        }
                                        else
                                        { 
                                            perror("read");
                                            close(fds_array[i]);        
                                            fds_array[i] = -1;
                                            continue;
                                        }
                                     }          
                                }
                                else if(s == 0)
                                { 
                                    printf("client is quit...\n");
                                    close(fds_array[i]);
                                    fds_array[i] = -1;
                                    continue;
                                }
                                else
                                { 

                                    perror("read");
                                    close(fds_array[i]);        
                                    fds_array[i] = -1;
                                    continue;
                                }
                            }
                        }//fi else
                    }//for
                }//default
        }//switch
    }//while
    return 0;
}
