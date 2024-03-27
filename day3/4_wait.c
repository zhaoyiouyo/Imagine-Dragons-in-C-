#include <54func.h>

int main(int argc, char *argv[]){
    int wstatus;
    if(fork()){
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            printf("exit status = %d\n", WEXITSTATUS(wstatus));
        }
        else if(WIFSIGNALED(wstatus)){
            printf("abnormal quit, terminal signal = %d\n", WTERMSIG(wstatus));
        }
    }
    else{
        system("./4_ls");
        return 0;
    }
    return 0;
}
