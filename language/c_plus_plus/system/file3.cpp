#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include<sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t g_mutex;
int g_cnt = 0;
int fd;

void* func1(void* child) {
        int times = 10000;  //通过参数传入需要写入的字节数
        int stat;
        //int fd;
        int i;
        
        struct timeval start,end;
        //fd = open("tmp.dat", O_WRONLY|O_CREAT, 0666);
        //fd = open("tmp.dat",O_WRONLY|O_CREAT|O_APPEND,0666);
        int childpid =1;
        //int childpid = int(child);
        if(fd < 0){
                perror("failed to open\n");
        }
        gettimeofday(&start,NULL);          //测试下时间
        if(childpid > 0){
                char *buf = (char*)malloc(times);
                for(int i = 0;i < times;++i) {
                    buf[i] = 'a';
                }
                strcat(buf,"\n");
                for(i=0; i< 10; i++){
                        usleep(1000);
                        write(fd,buf,strlen(buf));
                }
                //wait(&stat);
        }else{
                char *buf = (char*)malloc(times);
                for(int i = 0;i < times;++i) {
                    buf[i] = 'b';
                }
                strcat(buf,"\n");
                for(i=0; i<10; i++){
                        usleep(1000);
                        write(fd,buf,strlen(buf));
                }
        }
        close(fd);
        gettimeofday(&end,NULL);
}

void* func(void* child) {
        int times = 10000;  //通过参数传入需要写入的字节数
        int stat;
        //int fd;
        int i;
        
        struct timeval start,end;
        //fd = open("tmp.dat", O_WRONLY|O_CREAT, 0666);
        //fd = open("tmp.dat",O_WRONLY|O_CREAT|O_APPEND,0666);
        int childpid = -1;
        //int childpid = int(child);
        if(fd < 0){
                perror("failed to open\n");
        }
        gettimeofday(&start,NULL);          //测试下时间
        if(childpid > 0){
                char *buf = (char*)malloc(times);
                for(int i = 0;i < times;++i) {
                    buf[i] = 'a';
                }
                strcat(buf,"\n");
                for(i=0; i< 10; i++){
                        usleep(1000);
                        write(fd,buf,strlen(buf));
                }
                //wait(&stat);
        }else{
                char *buf = (char*)malloc(times);
                for(int i = 0;i < times;++i) {
                    buf[i] = 'b';
                }
                strcat(buf,"\n");
                for(i=0; i<10; i++){
                        usleep(1000);
                        write(fd,buf,strlen(buf));
                }
        }
        close(fd);
        gettimeofday(&end,NULL);
}

void *func2(void *arg)
{
    int loop = 3;
    int result = 1;
            //pthread_mutex_lock(&g_mutex);
            //g_cnt++;
            //loop--;
            //pthread_mutex_unlock(&g_mutex);
    return NULL;
}

int main(int argc, char **argv) {
    fd = open("tmp.dat", O_WRONLY|O_CREAT, 0666);
    //fd = open("tmp.dat", O_WRONLY|O_CREAT|O_APPEND,0666);
    pthread_t t1, t2;
    //pthread_mutex_init(&g_mutex, NULL);
    pthread_create(&t1, NULL, func, NULL);
    pthread_create(&t2, NULL, func1, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
