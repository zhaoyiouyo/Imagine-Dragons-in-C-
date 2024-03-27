#include <54func.h>

void Daemon(){
    if(fork()){
        exit(0);
    }
    setsid();
    for(int i = 0; i < 64; i++){
        close(i);
    }
    chdir("/");
    umask(0);
}

int main(){
    Daemon();
    for(int i = 0; i < 64; i++){
       syslog(LOG_INFO, "I am daemon , i = %d\n", i);
       sleep(2);
    }
    return 0;
}
