#include <stdio.h>
#include "bit_functions.h"


int main() 
{
    unsigned char a = 'A';

    printBitsIterative(a);
    printf("setting bits 2 and 3 \n");
    a = setBit(a, 2);
    a = setBit(a, 3);
    printBitsIterative(a);

    printf("clearing bit 2 \n");
    a = clearBit(a, 2);
    printBitsRecursive(a);

    return 0;
}
 

