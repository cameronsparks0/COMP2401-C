#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

int main(int argc, char *argv[]){
    char *param[5];
    int pid ,mid;
    int status;
    param[0] = "morphed";
    param[1] = "55";
    param[2] = "Second Command Parameter";
    param[3] = "Test!";
    param[4]= NULL;
    pid = fork();
    if (pid == 0) {
        // child process instructions
        int rc;
        rc = execv("./morphed",param);
        printf(" This should not be printed \n"); // this should not be executed because
        // the child is executing a new program
    }
    else {
        // parent process instructions
        mid = wait(&status);
        printf("Return code from morphed program: %d\n",WEXITSTATUS(status));
        printf("Parent program \n");
    }
}
