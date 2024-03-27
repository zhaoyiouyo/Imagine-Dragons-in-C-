#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "setsockopt");
    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "bind");
    listen(sockfd, 50);
    int netfd = accept(sockfd, NULL, NULL);

    int epfd = epoll_create(1);

    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &events);
    events.events = EPOLLIN;
    events.data.fd = netfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &events);
    char buf[1024] = {0};

    while(1){
        struct epoll_event readySet[2];
        int readyNum = epoll_wait(epfd, readySet, 2, -1);
        for(int i = 0; i < readyNum; i++){
            if(readySet[i].data.fd == STDIN_FILENO){
                bzero(buf, sizeof(buf));
                read(STDIN_FILENO, buf, sizeof(buf));
                send(netfd, buf, strlen(buf), 0);
            }
            else if(readySet[i].data.fd == netfd){
                bzero(buf, sizeof(buf));
                recv(netfd, buf, sizeof(buf), 0);
                printf("buf = %s\n", buf);
            }
        }
    }
    return 0;
}
