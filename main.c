#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gelenNode
{
    int id;
    char string[50];
    int id2;
    struct gelenNode* prev;
    struct gelenNode* next;
}gelenNode;
int main(int argc, char const *argv[]) {
    printf("Hello World!\n");
    printf("naber");
    printf("samet");
    for (int i = 0; i < 5; i++)
    {
        printf("%d",i);
        printf("merhaba");
        printf("devam");

    }
    return 0;
}
