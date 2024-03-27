#include <54func.h>

typedef struct node{
    int data;
    struct node *next;
}Link;

void *routine(void *arg){
    Link *head = (Link *)arg;
    Link *q = head -> next;
    while(q != NULL){
        printf("%d\n", q -> data);
        q = q -> next;
    }
    return NULL;
}

int main(){
    Link *head = (Link *)calloc(1, sizeof(Link));
    for(int i = 0; i < 5; i++){
        Link *p = (Link *)calloc(1, sizeof(Link));
        p -> data = i;
        p -> next = head -> next;
        head -> next = p;
    }
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, routine, head);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    sleep(1);
    return 0;
}
