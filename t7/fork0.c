

#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

//1.1a: Should appear twice.
//1.1b: Should appear four times.


int main()
{ 
    int pid;
    int i=0;
    
    printf("Ready to fork...\n"); 
    fork();	// create a clone
    fork();	// create a clone
    printf("after fork()\n");


}

