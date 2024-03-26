#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");
    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");
    write(fdw, "Helloworld", 10);
    char buf[1024] = {0};
    ssize_t sret1 = read(fdr, buf, sizeof(buf));
    printf("%s\n", buf);
    write(fdw, buf, sizeof(buf));
    return 0;
}
