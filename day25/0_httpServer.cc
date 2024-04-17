#include <string>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>
using namespace std;

class HttpServer
{
public:
    HttpServer(string ip, unsigned short port)
    : _ip(ip)
    , _port(port)
    , _sockfd(-1)
    {
        
    }

    ~HttpServer(){
        if(_sockfd > 0){
            close(_sockfd);
        }
    }

    //移动构造
    HttpServer(HttpServer &&other)
    : _ip(other._ip)
    , _port(other._port)
    , _sockfd(other._sockfd)
    {
        other._sockfd = -1;
    }

    HttpServer &operator = (HttpServer &&other){
        if(this != &other){
            _ip = other._ip;
            _port = other._port;

            if(_sockfd > 0){
                close(_sockfd);
            }

            _sockfd = other._sockfd;
            other._sockfd = -1;
        }
        return *this;
    }

    HttpServer(const HttpServer&) = delete;
    HttpServer &operator=(const HttpServer&) = delete;

    void start();
    void recvAndShow();
    string response();

private:
    string _ip;
    unsigned short _port;
    int _sockfd;
};

void HttpServer::start(){
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd < 0){
        perror("socket");
        exit(1);
    }

    int reuse = 1;
    int ret = setsockopt(_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    if(ret < 0){
        perror("setsockopt");
        exit(1);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_ip.c_str());
    serverAddr.sin_port = htons(_port);

    ret = ::bind(_sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    if(ret < 0){
        perror("bind");
        exit(1);
    }
    listen(_sockfd,10);
}

void HttpServer::recvAndShow(){
    while(true){
        // NULL ((void *)0)
        int netfd = accept(_sockfd,nullptr,nullptr);
        char buf[4096] = {0};
        ssize_t sret = recv(netfd,buf,sizeof(buf),0);
        printf("sret = %ld, buf = %s\n", sret, buf);
        string resp = response();
        send(netfd,resp.c_str(),resp.size(),0);
        close(netfd);
    }
}

string HttpServer::response(){
    string startLine = "HTTP/1.1 200 OK\r\n";
    string headers = "Server: MyHttpServer\r\n";
    int fd = open("联想截图_20230528204313.png",O_RDWR);
    ssize_t filesize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *buf = new char[filesize];
    read(fd,buf,filesize);
    string body(buf, filesize);
    headers += "Content-Type: image/png\r\n";
    headers += "Content-Length:" + std::to_string(body.size()) + "\r\n";
    string emptyLine = "\r\n";
    return startLine + headers + emptyLine + body;
}

int main(){
    HttpServer server("192.168.240.128",1234);
    server.start();
    server.recvAndShow();
    return 0;
}
