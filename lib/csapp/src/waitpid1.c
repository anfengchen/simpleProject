#include "csapp.h"

int main(int argc, char* argv[]){
    if(argc<2){
        fprintf(stderr,"argc must greater than 2.\n");
        exit(1);
    }

    int N = atoi(argv[1]);
    int status;
    pid_t pid;
    for(int i=0;i<N;i++){
        if(Fork()==0){
            exit(100+i);
        }
    }

    while ((pid=waitpid(-1,&status,0))>0)
    {
       if(WIFEXITED(status)){
           printf("child %d terminated normally with exit status=%d\n",pid,WEXITSTATUS(status));
       }else{
           printf("child %d terminated abnomally.\n",pid);
       }
    }
    
    if(errno != ECHILD){
        unix_error("waitpid error");
    }

    exit(0);
}