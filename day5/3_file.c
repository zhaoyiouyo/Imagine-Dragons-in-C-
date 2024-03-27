#include <54func.h>

void *routine1(void *arg){
    int *fd = (int *)arg;
    printf("fd = %d\n", *fd);
    sleep(3);
    char buff[1024] = {0};
    ssize_t ret = read(*fd, buff, sizeof(buff));
    printf("buff = %s\n", buff);
    return NULL;
}

void *routine2(void *arg){
    int *fd = (int *)arg;
    close(*fd);
    return NULL;
}

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd, -1, "open");
    printf("fd is open!\n");
    pthread_t tid1, tid2;
    int ret1 = pthread_create(&tid1, NULL, routine1, &fd);
    THREAD_ERROR_CHECK(ret1, "pthread_create");
    int ret2 = pthread_create(&tid2, NULL, routine2, &fd);
    THREAD_ERROR_CHECK(ret2, "pthread_create");
    printf("create is success\n");
    sleep(5);
    return 0;
}
