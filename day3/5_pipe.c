#include <54func.h>
int main(int argc, char *argv[])
{
    int fds1[2], fds2[2];
    pipe(fds1);
    pipe(fds2);
    if(fork()){
        close(fds1[0]);
        close(fds2[1]);
        write(fds1[1],"nihao",5);
        printf("write over!\n");
        close(fds1[1]);
        char buf[1024] = {0};
        read(fds2[0],buf,sizeof(buf));
        printf("I am parent, buf = %s\n", buf);
        wait(NULL);
    }
    else{
        close(fds1[1]);
        close(fds2[0]);
        char buf[1024] = {0};
        while(1){
            read(fds1[0],buf,1);
            sleep(1);
        }
        printf("I am child, buf = %s\n", buf);
        write(fds2[1],"hello",5);
        exit(0);
    }
    return 0;
}
