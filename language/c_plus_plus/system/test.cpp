#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 2
int Data[SIZE];

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t  notFull;
    pthread_cond_t  notEmpty;
    int read_point;
    int write_point;
}sCOND;

sCOND *pCondLock;

void init(void)
{
    //memset(pCondLock, 0, sizeof(sCOND));

    //1.Create a mutex lock
    pthread_mutex_init(&pCondLock->lock, NULL);

    //2.Create two condition variable  
    pthread_cond_init(&pCondLock->notFull, NULL);
    pthread_cond_init(&pCondLock->notEmpty, NULL);

    //set the read and write point 0
    pCondLock->read_point = 0;
    pCondLock->write_point = 0;
}


int put(int data) 
{
    //obtain the mutex lock
    pthread_mutex_lock(&pCondLock->lock);
    
    //check the global variable Data full or not
    while((pCondLock->write_point+1)%SIZE == pCondLock->read_point)
    {
        printf("The buf is full, waitting for not_full signal\n");
        pthread_cond_wait(&pCondLock->notFull, &pCondLock->lock);
    }       

    //write the data to buffer
    Data[pCondLock->write_point] = data;
    pCondLock->write_point++;
    if(pCondLock->write_point == SIZE)
        pCondLock->write_point = 0;
    
    //unlock the mutex lock 
    pthread_mutex_unlock(&pCondLock->lock);

    //wake up the not_empty signal
    pthread_cond_signal(&pCondLock->notEmpty);
        

    return 0;
}


int get(int *data) 
{
    //obtain the mutex lock
    pthread_mutex_lock(&pCondLock->lock);
    
    //check the global variable Data empty or not
    while(pCondLock->write_point == pCondLock->read_point)
    {
        printf("The buf is empty, waitting for not_empty signal\n");
        pthread_cond_wait(&pCondLock->notEmpty, &pCondLock->lock);
    }       

    //read the data from buffer
    *data = Data[pCondLock->read_point];
    pCondLock->read_point++;
    if(pCondLock->read_point == SIZE)
        pCondLock->read_point = 0;
    
    //wake up the not_empty signal
    pthread_cond_signal(&pCondLock->notFull);
        
    pthread_mutex_unlock(&pCondLock->lock);

    return *data;
}

void *produce(void)
{
    int times=0;
    //1. first 5 times, every second write a data to buffer
    for(times=0; times < 5; times++)
    {
        sleep(1);
        put(times+1);
        printf("Input date=%d\n", times+1);
    }

    //2. last 5 times, every 3 seconds write a data to buffer 
    for(times = 5; times < 10; times++)
    {
        sleep(3);
        put(times+1);
        printf("Input date=%d\n", times+1);
    }
}

void *consume(void)
{
    int times=0;
    int data=0;
    //10 times, every 2 seconds read the buffer
    for(times = 0; times < 10; times++)
    {
        sleep(2);
        data = get(&data);
        printf("The data is %d\n", data);
    }
}

int main()
{
    pthread_t tid1, tid2;
    
    pCondLock = malloc(sizeof(sCOND));
    memset(pCondLock, '\0', sizeof(sCOND));
    //1.init the struct of sCondLock 
    init();

    //2. start two threads
    pthread_create(&tid1, NULL, (void*)*produce, NULL);
    pthread_create(&tid2, NULL, (void*)*consume, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    free(pCondLock);

    return 0;
}
