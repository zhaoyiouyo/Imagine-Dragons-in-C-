#include <54func.h>

void handler(int signum){
    printf("before signum = %d\n", signum);
    sleep(5);
    printf("after signum = %d\n", signum);
}

int main(){
    signal(SIGINT, handler);
    while(1){
        sleep(1);
    }
    return 0;
}
