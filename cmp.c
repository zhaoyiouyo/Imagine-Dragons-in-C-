#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int fd1 = open(argv[1], O_RDWR);
    ERROR_CHECK(fd1, -1, "open");
    int fd2 = open(argv[2], O_RDWR);
    ERROR_CHECK(fd2, -1, "open");
    char buf1[5] = {0};
    char buf2[5] = {0}; 
    while(1){
        memset(buf1, 0, sizeof(buf1));
        ssize_t sret1 = read(fd1, buf1, sizeof(buf1));
        ERROR_CHECK(sret1, -1, "read");
        memset(buf2, 0, sizeof(buf2));
        ssize_t sret2 = read(fd2, buf2, sizeof(buf2));
        ERROR_CHECK(sret2, -1, "read");
        if(memcmp(buf1, buf2, sizeof(buf1)) != 0){
            printf("内容不一致");
            break;
        }
        if(sret1 == 0){
            printf("内容相符");
            break;
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}
