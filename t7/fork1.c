

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

int main()
{ 
    int pid, cpid;
    int i=0;
    int status;
    
    printf("Ready to fork...\n"); 
    pid = fork();	// create a clone

    if(pid==0){
        printf("Child process pid=%d parent process id=%d\n",getpid(),getppid());
        return(55);
    }
    else if(pid > 0){
        cpid = wait(&status);
        printf("Child has returned the value %d\n",WEXITSTATUS(status));
        if(WIFEXITED(status)){
            printf("Exited Correctly\n");
        }
        printf("\t Parent process pid=%d child process id=%d\n",getpid(),pid);
        return(0);
    }
    else{
        printf("\t ERROR - parent process pid=%d could not fork a child process \n",getpid());
        return(1);
    }

}

