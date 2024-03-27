#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);

    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_write");

    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_read");

    char buf[1024] = {0};
    fd_set rdset;

    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);
        select(fdr + 1, &rdset, NULL, NULL, NULL);
        
        if(FD_ISSET(STDIN_FILENO, &rdset)){
            memset(buf, 0, sizeof(buf));
            ssize_t sret = read(STDIN_FILENO, buf, sizeof(buf));
            time_t now = time(NULL);
            printf("%s\n", ctime(&now));
            if(sret == 0){
                printf("阿珍主动结束聊天！\n");
                break;
            }
            write(fdw, buf, sizeof(buf));
        }

        if(FD_ISSET(fdr, &rdset)){
            memset(buf, 0, sizeof(buf));
            ssize_t sret = read(fdr, buf, sizeof(buf));
            if(sret == 0){
                printf("阿强结束了聊天！\n");
                break;
            }
            printf("阿强说：%s\n", buf);
        }
    }
    return 0;
}
