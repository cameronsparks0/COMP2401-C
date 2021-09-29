// File is str_cmp_main.c
/* The file is a test file for the string comparison functions
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

int main(int argc, char* argv[])
{

    char *s1 = "Monday";
    char *s2 = "Monster day";


	printf("Answer should be -1 myStrCmp= %d \n", myStrCmp(s1, s2));
	printf("Answer should be 1 myStrCmp= %d \n", myStrCmp(s2, s1));

	// note that here the program passess subsections of the original strings as 
	// strings to the comparison function
	printf("Answer should be 0 myStrCmp= %d \n", myStrCmp(&s1[3], &s2[8]));
    

    return 0;
}
