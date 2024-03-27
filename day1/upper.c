#include <54func.h>

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    int size = lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET);
    int ret = ftruncate(fd, size);
    ERROR_CHECK(ret, -1, "ftruncate");

    char *p = (char *)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    for(int i; i < size; i++){
        if(p[i] >= 'a' && p[i] <= 'z'){
            p[i] -= 32;
        }
        if(ispunct(p[i])){
            p[i] = ' ';
        }
    }
    munmap(p, size);
    close(fd);
    return 0;
}
