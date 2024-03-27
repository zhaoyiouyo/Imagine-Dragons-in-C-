#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open_read");

    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open_write");

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
                printf("阿强主动结束聊天！\n");
                break;
            }
            write(fdw, buf, sizeof(buf));
        }

        if(FD_ISSET(fdr, &rdset)){
            memset(buf, 0, sizeof(buf));
            ssize_t sret = read(fdr, buf, sizeof(buf));
            if(sret == 0){
                printf("阿珍结束了聊天！\n");
                break;
            }
            printf("阿珍说：%s\n", buf);
        }
    }
    return 0;
}
