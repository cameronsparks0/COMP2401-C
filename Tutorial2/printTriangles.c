/* File is printTriangles.c

Purpose: file is for tutorial 2 to explore recursion


Revision:
a. Initial code - Doron Nussbaum 14/9/2018
b. Revision to remove unused prototypes and change return types

*/

/************************************************************************/

// INCLUDE FILES

#include "stdio.h"
#include "stdlib.h"


/************************************************************************/
// FUNCTION PROTOTYPES

void printTriangleRecursive(unsigned int numRows);
void printTriangleRecursiveUpsidedown(unsigned int numRows);
void printTriangleRecursiveCountStars(unsigned int numRows, int *numStars);

/************************************************************************/


int main()
{

  unsigned int numRows=7;
	int numStars=0;
  int j;

	printf("printing a triangle with %d rows \n",numRows);
	printTriangleRecursive(numRows);
 
	printf("\nprinting a triangle upside down with %d rows \n\n",numRows);
	printTriangleRecursiveUpsidedown(numRows);

	printf("\nprinting a triangle with %d rows and counting the number of stars\n\n",numRows);
	printf("the number of printf * should be %d \n", (1+numRows)*numRows/2);
	printTriangleRecursiveCountStars(numRows, &numStars);
	printf("\nthe number of * returned by the function is %d\n\n",numStars);

	return(0);
}


/***********************************************************************************/
/* Purpose: prints a triangle using '*'

input:
numRows - the number of rows that the triangle should have

output:
none

return:

*/


void printTriangleRecursive(unsigned int numRows)
{

	if(numRows==1){ //Base Case
		printf("*\n");
	}

	else{
		printTriangleRecursive(numRows-1); //Recursive step
		for(int x=0;x<numRows;x++){ //Action
			printf("*");
		}
		printf("\n");
	}
    return;

}


/***********************************************************************************/
/* Purpose: prints a triangle using '*' and computes how many '*' were printed

input:
numRows - the number of rows that the triangle should have

output:
numStars - the number of stars that were printed

return:
*/


void printTriangleRecursiveCountStars(unsigned int numRows, int *numStars)
{

	if(numRows==1){ //Base Case
		printf("*\n");
		*numStars = *numStars + 1;
	}

	else{
		printTriangleRecursiveCountStars(numRows-1,numStars); //Recursive step
		for(int x=0;x<numRows;x++){ //Action
			printf("*");
			*numStars = *numStars + 1;
		}
		printf("\n");
	}
    return;
}




/***********************************************************************************/
/* Purpose: prints a triangle using '*' with the base as the first row

input:
numRows - the number of rows that the triangle should have

output:
none

return:

*/


void printTriangleRecursiveUpsidedown(unsigned int numRows)
{

	if(numRows==1){ //Base Case
		printf("*\n");
	}

	else{
		for(int x=0;x<numRows;x++){ //Action
			printf("*");
		}
		printf("\n");
		printTriangleRecursiveUpsidedown(numRows-1); //Recursive step
	}
    return;
}

