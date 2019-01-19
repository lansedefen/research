#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include<sys/wait.h>

int main(int argc,char * argv[])
{
    struct timeval start,end;
        int times = argc > 1 ? atoi(argv[1]):10000;  //通过参数传入需要写入的字节数
        int stat;
        int fd;
        int childpid;
        int i;

        fd = open("tmp.dat", O_WRONLY|O_CREAT, 0666);
        for(i=0 ;i<1; i++){
                if(childpid = fork())
                        break;
        }

        if(childpid == -1){
                perror("failed to fork\n");
                return 1;
        }

        //fd = open("tmp.dat", O_WRONLY|O_CREAT, 0666);
        //fd = open("tmp.dat",O_WRONLY|O_CREAT|O_APPEND,0666);
        if(fd < 0){
                perror("failed to open\n");
                return 1;
        }

        gettimeofday(&start,NULL);          //测试下时间
        if(childpid > 0){
                char *buf = (char*)malloc(times);
                for(int i = 0;i < times;++i) {
                    buf[i] = 'a';
                }
                strcat(buf,"\n");
                for(i=0; i< 20; i++){
                        usleep(1000);
                        write(fd,buf,strlen(buf));
                }
                wait(&stat);
        }else{
                char *buf = (char*)malloc(times);
                for(int i = 0;i < times;++i) {
                    buf[i] = 'b';
                }
                strcat(buf,"\n");
                for(i=0; i<20; i++){
                        usleep(1000);
                        write(fd,buf,strlen(buf));
                }
        }
        close(fd);
        gettimeofday(&end,NULL);

        int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        printf("UseTime: MicroSeconds:%d us and  Seconds:%d s\n",timeuse,end.tv_sec-start.tv_sec);
        return 0;
}
