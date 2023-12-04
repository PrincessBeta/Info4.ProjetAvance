#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include"liste.h"

int main()
{
    List *l = list_create();
    int* i = malloc(sizeof(int));
    int* j = malloc(sizeof(int));
    *i = 1;
    *j = 2;
    
    list_push_front(l,i);
    list_push_front(l,j);
    
    printf("%d \n",*(int*)list_front(l));
    l = list_pop_front(l);
    printf("%d \n",*(int*)list_front(l));


    return 0;
}
