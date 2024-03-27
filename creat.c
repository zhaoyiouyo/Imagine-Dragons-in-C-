#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);
    int fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd, -1, "open_read");

    int ret = mkdir(argv[2], 0777);
    ERROR_CHECK(ret, -1, "mkdir");

    char name[50] = {0};
    int size_name = 0;

    int size_file = 0;
    char buf[4096] = {0};

    read(fd, &size_name, sizeof(int));
    read(fd, name, size_name);
    read(fd, &size_file, sizeof(int));
    read(fd, buf, size_file);

    char path[1024] = {0};
    sprintf(path, "%s%s%s", argv[2], "/", name);

    int fd_file = open(path, O_RDWR|O_CREAT, 0777);
    ERROR_CHECK(fd_file, -1, "open_file");
    write(fd_file, buf, size_file);
    printf("创建成功！\n");
    return 0;
}
