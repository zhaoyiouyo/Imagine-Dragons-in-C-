#include <54func.h>

typedef struct node{
    int data;
    struct node *next;
}Link;

void *routine(void *arg){
    Link *head = (Link *)arg;
    printf("child data = %d\n", head -> data);
    return NULL;
}

int main(){
    Link *head = (Link *)calloc(1, sizeof(Link));
    head -> data = 1000;
    printf("main data = %d\n", head -> data);
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, routine, head);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    free(head);
    sleep(1);
    return 0;
}
