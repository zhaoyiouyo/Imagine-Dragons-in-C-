#include <54func.h>

typedef struct student{
    int st_id;
    char name[100];
    float cent;
}student;

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    student s[3] = {{101, "anna", 98},{102, "kity", 65},{103, "bee", 99}};
    ssize_t sretw = write(fd, s, sizeof(s));
    lseek(fd, 0, SEEK_SET);
    student buf[3] = {0};
    ssize_t sretr = read(fd, buf, sizeof(buf));
    for(int i = 0; i < 3; i++){
        printf("%d %s %.2f", buf[i].st_id, buf[i].name, buf[i].cent);
    }
    return 0;
}
