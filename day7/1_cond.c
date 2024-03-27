#include <54func.h>

typedef struct share_s{
    pthread_mutex_t mutex;
    int flag;
    pthread_cond_t cond;
}share_t;

void A(){
    printf("A\n");
}
void B(){
    printf("B\n");
}
void C(){
    printf("C\n");
}

void *threadFunc(void *arg){
    sleep(3);
    share_t *share = (share_t *)arg;
    pthread_mutex_lock(&share->mutex);
    while(share->flag != 1){
        pthread_cond_wait(&share->cond, &share->mutex);
    }
    B();
    share->flag = 2;
    pthread_cond_signal(&share->cond);
    pthread_mutex_unlock(&share->mutex);
    pthread_exit(NULL);
}

int main(){
    share_t share;
    share.flag = 0;
    pthread_mutex_init(&share.mutex, NULL);
    pthread_cond_init(&share.cond, NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc, &share);

    A();
    pthread_mutex_lock(&share.mutex);
    share.flag = 1;
    pthread_cond_signal(&share.cond);
    while(share.flag != 2){
        pthread_cond_wait(&share.cond, &share.mutex);
    }
    pthread_mutex_unlock(&share.mutex);
    C();

    pthread_join(tid, NULL);
    return 0;
}
