#include <stdio.h>  

#define ASCIIMAX 127

int main()  
{  
    char testString[100];
    printf("Please Enter A String: ");
    scanf("%s",testString);
    printf("\n");

    for(int i=0 ; testString[i]!=0 ; i++ ) /*ASCII values ranges from 0-127*/  
    {  
        printf("ASCII Code for character %c = %d\n", testString[i], testString[i]);  
    }  

    return 0;  
}   
