#include<pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include<iostream>
#include <sys/syscall.h>

using namespace std;

typedef struct st_ThreadNode
{
	//pthread_mutex_t mutex;
	FILE*			pFile;
	int				nNum;
}st_ThreadNode;

pthread_mutex_t mutex;
st_ThreadNode stTNode;

void* thread_func(void* ptr)
{
	st_ThreadNode* pNode = (st_ThreadNode*)ptr;
	FILE* pf = pNode->pFile;
	int ret = 0;
	char szLine[1024*10] = {0};
    sleep(1);

	while(1)
	{
		pthread_mutex_lock(&mutex);
		//pthread_mutex_lock(&pNode->mutex);
		if(fgets(szLine, 1024*10, pf) == NULL)
		{
			pthread_mutex_unlock(&mutex);
			//pthread_mutex_unlock(&pNode->mutex);
			return 0;
		}

		//pthread_mutex_unlock(&pNode->mutex);
        cout << szLine << ",pid:" << getpid() << ", tid:" << syscall(SYS_gettid) <<", thread_id:" << pthread_self() << endl; ;
		pthread_mutex_unlock(&mutex);
		usleep(2);
		//pthread_mutex_lock(&mutex);
		//pthread_mutex_lock(&pNode->mutex);

		//pNode->nNum++;
		//if(pNode->nNum%1000 == 0)
		//{
		//	time_t tNow = time(0);
		//	struct tm* stTime = localtime(&tNow);
		//	printf("%02d:%02d:%02d num log\n", stTime->tm_hour, stTime->tm_min, stTime->tm_sec);
		//}
		//pthread_mutex_unlock(&pNode->mutex);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	std::string stUidFile = argv[1];

	FILE* pf = fopen(stUidFile.c_str(), "rb");
	stTNode.pFile = pf;
	pthread_mutex_init(&mutex, NULL);
	//pthread_mutex_init(&stTNode.mutex, NULL);

	int nThreadNum = 3;
	pthread_t TList[nThreadNum];
	for(int i = 0; i < nThreadNum; i++)
	{
		int ret_thread = pthread_create(&TList[i], NULL, thread_func, (void*)(&stTNode));
		printf("subthread start %d, %d", i, ret_thread);
	}

	for(int i = 0; i < nThreadNum; i++)
	{
		pthread_join(TList[i], NULL);
	}	

	usleep(1000);
	return 0;
}
