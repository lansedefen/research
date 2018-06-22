#include<pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include<iostream>
#include<resource_ext.h>
#include<repost_resource.h>

using namespace std;

int init() {
    const char* class_name = "1";
    ResourceExt::Init("./", class_name);
    return -1;
}

typedef struct st_ThreadNode
{
	pthread_mutex_t mutex;
	int				nNum;
} st_ThreadNode;

void* run(void* ptr)
{
    //init();
    const char* key = "final_hot_tp";
    const char* class_name = "1";
	HOTTOPIC_DICT* pdict = ResourceExt::Reference<HOTTOPIC_DICT> (key, class_name);
    cout << "pdict:" <<pdict <<endl;
    pdict->UnReference();
    //    return -1;
}

int main(int argc, char* argv[])
{
    // init 
    init();

    // run 
    st_ThreadNode stTNode;
	pthread_mutex_init(&stTNode.mutex, NULL);
	int nThreadNum = 5;
	pthread_t TList[nThreadNum];
	for(int i = 0; i < nThreadNum; i++)
	{
		int ret_thread = pthread_create(&TList[i], NULL, run, (void*)(&stTNode));
		printf("subthread start %d, %d", i, ret_thread);
	}

	usleep(1000);
	for(int i = 0; i < nThreadNum; i++)
	{
		pthread_join(TList[i], NULL);
	}	

    // reload
    const char* key = "final_hot_tp";
    const char* class_name = "1";
    ResourceExt::DynReload(key, class_name);

	return 0;
}
