#include<stdio.h>
#include<stdlib.h>

#define MAX_LENGTH 3 //Max amount of characters needed to store user input.

void printVars(unsigned char acd){ //Used a char due to a pointer being 8 bytes and a char being 1 (Reduces memory footprint)
    printf("In Character Form: %c\n",acd);

    printf("In Decimal Form: %d\n",acd);

    printf("In Binary Form: ");
    for(int x=2;x>=0;x--)
    (acd & (1<<x))>>x==1 ? printf("1") : printf("0"); // Grabbing each bit of acd using a bit mask operator and displaying it.

    printf("\n");
}

int main(int argc, char **argv){
    unsigned char tempStorage[MAX_LENGTH]; //Temporary char array that stores the user input
    unsigned char acd=0b00000000; // Smallest primitive type to store permissions in (1 byte)
    
    printf("Welcome to the permission entry program!\n");
    printf("Please enter the 3-letter sequence of permissions(y or n ONLY): ");
    scanf("%s",tempStorage);
    
    for(int x=2;x>=0;x--)
    acd = (tempStorage[x]==121) ? acd | (1<<(2-x)) : acd & (~(1<<(2-x))); // Using a bit mask operator to set acds bits ("y"=1 "n"=0)

    printVars(acd);

    return(EXIT_SUCCESS);
}
