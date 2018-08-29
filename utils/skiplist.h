#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__
#include <iostream>
#include <ctime>
#define MAX_LEVEL 16
#define newNodeOfLevel(l) (Node*)malloc(sizeof(Node) + l * sizeof(Node*));

struct Node{
    int key;
    int value;
    Node *forward[1];
};
struct skiplist{
    int level; // max level ot the list
    Node *header;
};

int randomLevel()
{
    int k=0;
    while (rand()%2) k++;
    k = k < MAX_LEVEL ? k : MAX_LEVEL;
    return k;
}

void printSL(skiplist *sl)
{
    Node *p,*q;
    int k=sl->level;
    for(int i=k; i >= 0; i--)
    {
        p = sl->header->forward[i];
        printf("level[%d]: ",i);
        while(p->forward[i] != NULL)
        {
            printf("%d -> ",p->value);
            p = p->forward[i];
        }
        printf("%d\n",p->value);
    }
    printf("\n");
}
#endif