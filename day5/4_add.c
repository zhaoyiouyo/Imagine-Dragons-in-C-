#include <54func.h>

int num = 0;

void *routine1(void *arg){
    for(int i = 0; i < 10000000; i++){
        num++;
    }
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t tid1;
    int ret1 = pthread_create(&tid1, NULL, routine1, NULL);
    THREAD_ERROR_CHECK(ret1, "pthread_create");
    int ret2 = pthread_create(&tid1, NULL, routine1, NULL);
    THREAD_ERROR_CHECK(ret2, "pthread_create");
    printf("create is success\n");
    sleep(20);
    printf("num = %d\n", num);
    return 0;
}
