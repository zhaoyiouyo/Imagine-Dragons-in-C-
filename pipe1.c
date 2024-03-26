#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");
    char buf[1024] = {0};
    ssize_t sret = read(fdr, buf, sizeof(buf));
    printf("%s\n", buf);
    write(fdw, buf, sizeof(buf));
    memset(buf, 0, sizeof(buf));
    ssize_t sret1 = read(fdr, buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;
}
