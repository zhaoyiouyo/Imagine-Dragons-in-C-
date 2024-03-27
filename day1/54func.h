#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <ctype.h>
#include <syslog.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <pthread.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <mysql/mysql.h>
#include <crypt.h>
#define ARGS_CHECK(argc,num) {if(argc!=num){fprintf(stderr,"args error!\n");return -1;}}
#define ERROR_CHECK(ret,num,msg) {if(ret == num){perror(msg); return -1;}}
#define THREAD_ERROR_CHECK(ret,msg) {if(ret != 0){fprintf(stderr,"%s:%s\n",msg,strerror(ret));}}
