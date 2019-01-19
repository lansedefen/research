#include <stdio.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

#define SIZE 128

hash_map<string, int> myhash;
pthread_mutex_t mutex;
int EXIT = 0;
char word[SIZE];

void* child(void *arg)
{
        pthread_mutex_lock(&mutex);
        printf("The input words: %s\n", word);
        pthread_mutex_unlock(&mutex);
}

int main()
{
    //1. create the lock
    pthread_mutex_init(&mutex, NULL);
    //myhash.insert (make_pair<string, int>("eggs", 6)); 

    //2.create a new thread
	int nThreadNum = 3;
	pthread_t TList[nThreadNum];
	for(int i = 0; i < nThreadNum; i++)
	{
        pthread_t tid;
        int ret_thread = pthread_create(&tid, NULL, child, NULL);
        TList[i] = tid; 
		printf("subthread start %d, %d\n", i, ret_thread);
	}

	for(int i = 0; i < nThreadNum; i++)
	{
		pthread_join(TList[i], NULL);
	}	

    printf("The child has joined\n");
    pthread_mutex_destroy(&mutex);

    return 0;
}
