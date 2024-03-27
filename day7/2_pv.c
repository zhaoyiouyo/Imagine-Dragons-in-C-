#include <54func.h>

typedef struct node_s{
    int data;
    struct node_s *next;
}node_t;
typedef struct list_s{
    node_t *head;
    node_t *tail;
}list_t;

void queueEnter(list_t *list, int data){
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
    pNew->data = data;
    if(list->head == NULL){
        list->head = pNew;
        list->tail = pNew;
    }
    else{
        list->tail->next = pNew;
        list->tail = pNew;
    }
    //printf("生产的商品编号：%d\n", data);
}

void queueExit(list_t *list){
    node_t *p = list->head;
    list->head = list->head->next;
    //printf("消费的商品编号：%d\n", p->data);
    free(p);
}

void queueVisit(list_t *list){
    node_t *pCur = list->head;
    printf("当前商品有：");
    while(pCur){
        printf("%d号 ", pCur->data);
        pCur = pCur->next;
    }
    printf("\n");
}

typedef struct share_s{
    pthread_mutex_t mutex;
    int flag;
    pthread_cond_t cond;
    list_t *list;
}share_t;

void *producer(void *arg){
    share_t *share = (share_t *)arg;
    while(1){
        sleep(3);
        pthread_mutex_lock(&share->mutex);
        while(share->flag >= 10){
            pthread_cond_wait(&share->cond, &share->mutex);
        }
        queueEnter(share->list, rand()%10);
        queueVisit(share->list);
        share->flag++;
        pthread_cond_broadcast(&share->cond);
        pthread_mutex_unlock(&share->mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg){
    share_t *share = (share_t *)arg;
    while(1){
        sleep(1);
        pthread_mutex_lock(&share->mutex);
        while(share->flag <= 0){
            pthread_cond_wait(&share->cond, &share->mutex);
        }
        queueExit(share->list);
        queueVisit(share->list);
        share->flag--;
        pthread_cond_broadcast(&share->cond);
        pthread_mutex_unlock(&share->mutex);
    }
    pthread_exit(NULL);
}

int main(){
    share_t share;
    share.list->head = NULL;
    share.list->tail = NULL;

    srand(time(NULL));
    for(int i = 0; i < 8; i++){
        queueEnter(share.list, rand()%10);
    }

    share.flag = 8;
    pthread_mutex_init(&share.mutex, NULL);
    pthread_cond_init(&share.cond, NULL);

    pthread_t pro1, pro2, pro3, con1, con2;
    pthread_create(&pro1, NULL, producer, &share);
    pthread_create(&pro2, NULL, producer, &share);
    pthread_create(&pro3, NULL, producer, &share);
    sleep(5);
    pthread_create(&con1, NULL, consumer, &share);
    pthread_create(&con2, NULL, consumer, &share);

    pthread_join(pro1, NULL);
    pthread_join(pro2, NULL);
    pthread_join(pro3, NULL);
    pthread_join(con1, NULL);
    pthread_join(con2, NULL);
    return 0;
}
