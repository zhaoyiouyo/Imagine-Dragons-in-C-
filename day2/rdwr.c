#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fdr = open(argv[1], O_RDWR);
    ERROR_CHECK(fdr, -1, "open");
    int fdw = open(argv[1], O_RDWR);
    ERROR_CHECK(fdw, -1, "open");
    printf("管道打开！\n");
    
    fd_set rdset;
    fd_set wrset;
    int cnt_rd = 0;
    int cnt_wr = 0;
    char buf[4096] = {0};
    while(1){
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(fdr, &rdset);
        FD_SET(fdw, &wrset);
        int ret = select(fdw + 1, &rdset, &wrset, NULL, NULL);

        if(FD_ISSET(fdr, &rdset)){
            read(fdr, buf, 1024);
            printf("已读，第%d次读取，ret = %d\n", ++cnt_rd, ret);
        }
        if(FD_ISSET(fdw, &wrset)){
            write(fdw, buf, 4096);
            printf("已写，第%d次写入，ret = %d\n", ++cnt_wr, ret);
        }
        sleep(2);
    }
    return 0;
}
