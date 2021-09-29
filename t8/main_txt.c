
/*************************************************************/

// INCLUDES 
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

/*************************************************************/

// prototypes 

int fexists(char *fileName);
void readFile(FILE *fid);

/*************************************************************/

 
int main(int argc, char *argv[]) {

  FILE *fid;
  int rc=0;


  // TODO: add work also goes in this function.
  
  // check the number of command line parmeters 
  // if incorrect number print message and exits
  if (argc < 2) {
      printf("usage %s filename \n",argv[0]);
      return(1);
  }

  // check if file exists
  rc = fexists(argv[1]);

  // print message depending whether the file exists
  if(rc){
      printf("The filename exists");
      fid = fopen(argv[1], "r");
      readFile(fid);
  }
  else{
      printf("The filename does not exist");
  }


  return 0;
}


/*********************************************************************/
// Return whether the given file exists in the current directory.
// 
// Input:
// fileName - name of fle
//
// Output:
// None
//
// Return:
// 0 if the file does not exist
// 1 if the file exists
//
int fexists(char *fileName)
{
    // add code

    FILE *fp = NULL;
    int rc = 0;

	// open the file

    fp = fopen(fileName, "r");

	// determine the recturn code
    if(!fp){
        return 0;
    }
    else{
        fclose(fp);
        return 1;
    }




    return(rc);
}




/*********************************************************************/
// Read the content of the file 
// 
// Input:
// fid - file handle 
//
// Output:
// None
//
// Return:
// 0 if the file does not exist
// 1 if the file exists
//
void readFile(FILE *fid)
{
    // add code
    char fName[30];
    char lName[30];
    int age;

    while(!feof(fid)){
        fscanf(fid,"%30c",fName);
        fscanf(fid,"%30c",lName);
        fscanf(fid,"%d",&age);

        printf("\n%s%s%d\n",fName,lName,age);

    }

    fclose(fid);

	// while not end of file

	// read a values in a line

	// print the values to the screen 

}
