#include <54func.h>
int val = 0;
void *threadFunc(void *arg){
    pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
    while(1){
        pthread_mutex_lock(mutex);
        if(val == 1) break;
        pthread_mutex_unlock(mutex);
    }
    printf("Before B!\n");
    sleep(3);
    printf("After B\n");
    pthread_exit(NULL);
}
int main(){
    pthread_t tid;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid, NULL, threadFunc, &mutex);
    printf("Before A!\n");
    sleep(3);
    printf("After A\n");
    pthread_mutex_lock(&mutex);
    val = 1;
    pthread_mutex_unlock(&mutex);
    pthread_join(tid, NULL);
    return 0;
}
