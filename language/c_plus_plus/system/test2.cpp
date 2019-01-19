#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 128

pthread_mutex_t mutex;
int EXIT = 0;
char word[SIZE];

void* child(void *arg)
{
    while(1)
    {
        while(strlen(word) == 0)
            usleep(100);

        pthread_mutex_lock(&mutex);
        printf("The input words: %s\n", word);
        pthread_mutex_unlock(&mutex);
        if(strcmp("end\n", word) == 0)
        {
            printf("The process end\n");
            EXIT = 1;
            break;
        }
        memset(word, '\0', SIZE);
    }
    ;
}

int main()
{
    //1. create the lock
    pthread_mutex_init(&mutex, NULL);
    
    //2.create a new thread
    pthread_t tid;
    pthread_create(&tid, NULL, child, NULL);
    
    //3. Input words
    while(EXIT == 0)
    {
        if(strlen(word)!=0)
            usleep(100);
        //add the lock
        else
        {
            pthread_mutex_lock(&mutex);
            printf("Input words:  ");
            fgets(word, SIZE, stdin);
            pthread_mutex_unlock(&mutex);            
        }
    }

    pthread_join(tid, NULL);
    printf("The child has joined\n");
    pthread_mutex_destroy(&mutex);

    return 0;
}
