#include <54func.h>
#define NUM 10000000

int val = 0;

typedef struct share_s{
    pthread_mutex_t mutex;
}share_t;

void *threadFunc(void *arg){
    share_t *pshare = (share_t *)arg;
    for(int i = 0; i < NUM; i++){
        pthread_mutex_lock(&pshare->mutex);
        ++val;
        pthread_mutex_unlock(&pshare->mutex);
    }
    pthread_exit(NULL);
}

int main(){
    share_t share;
    pthread_mutex_init(&share.mutex, NULL);

    struct timeval start, end;

    pthread_t tid;
    gettimeofday(&start, NULL);
    pthread_create(&tid, NULL, threadFunc, &share);

    for(int i = 0; i < NUM; i++){
        pthread_mutex_lock(&share.mutex);
        ++val;
        pthread_mutex_unlock(&share.mutex);
    }
    pthread_join(tid, NULL);
    gettimeofday(&end, NULL);
    printf("val = %d, total time = %ld us\n", val, (end.tv_sec - start.tv_sec)*1000*1000 + end.tv_usec - start.tv_usec);
    return 0;
}
