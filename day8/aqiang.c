#include <54func.h>
int main(int argc, char *argv[])
{
    // ./5_aqiang 192.168.72.128 1234
    // 192.168.72.128:1234 是服务端的ip端口
    ARGS_CHECK(argc,3);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"connect");
    
    char buf[4096] = {0};
    while(1){
            bzero(buf,sizeof(buf));
            recv(sockfd,buf,sizeof(buf),0);
            printf("buf = %s\n", buf);

            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(sockfd,buf,strlen(buf),0);
    }

    return 0;
}
