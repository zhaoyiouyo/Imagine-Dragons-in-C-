#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int fd = open(argv[1], O_WRONLY);
    ERROR_CHECK(fd, -1, "open");

    int fd_file = open(argv[2], O_RDONLY);
 
    char name[50] = {0};
    sprintf(name, "%s", argv[2]);
    int size_name = strlen(argv[2]);
    char buf[1024] = {0};
    ssize_t sret = read(fd_file, buf, sizeof(buf));

    write(fd, &size_name, sizeof(int));
    write(fd, name, size_name);
    write(fd, &sret, sizeof(ssize_t));
    write(fd, buf, sret);
    printf("发送成功！\n");
    return 0;

}
