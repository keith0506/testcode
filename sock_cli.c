#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

static void usage(const char* proc)  //使用说明
{ 
     printf("Usage:%s [local_ip] [local_port]\n", proc);
}

//tcp_client server_ip server_port
int main(int argc, char* argv[])
{ 
    if(argc != 3)
    { 
        usage(argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM , 0);
    if(sock < 0)
    { 
        perror("socket\n");
        return 2;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    { 
        perror("connect\n");
        return 3;
    }

    umask(0);
    int fd = open("./log", O_WRONLY|O_CREAT, 0644);
    if(fd < 0)
    { 
        perror("open");
        return 4;
    }
    close(1);
    int ret = dup2(fd, 1);

    printf("connect success\n");
    char buf[1024];
    while(1)
    { 
        printf("please Enter# \n");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf)-1);
        if(s > 0)
        { 
            buf[s-1] = 0;
            write(sock, buf, strlen(buf));
            s = read(sock, buf, sizeof(buf)-1);
            if(s > 0)
            { 
                buf[s] = 0;
                printf("server echo# %s\n ", buf);
            }
        }
    }
    close(fd);
    close(sock);
    return 0;
}
