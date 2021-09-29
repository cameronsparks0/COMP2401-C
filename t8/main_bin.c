#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"

int fexists(char *fileName);
void readFile(FILE *fid);

int main(int argc, char *argv[]) {

  struct personalInfo person;
  FILE *fid;
  int i;
  int rc;

// add coded


  // if the file does not exist print message

  rc = fexists(argv[1]);

  // print message depending whether the file exists
  if(rc){
      fid = fopen(argv[1], "rb+");
      readFile(fid);
  }
  else{
      printf("The filename does not exist");
  }

  // open the file

  // read first record

  // print the record

  // close the file


  return 0;
}

/************************************************************************/
// Return whether the given file exists in the current directory.
// TODO: Complete this function.
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

void readFile(FILE *fid)
{
    // add code
    personalInfo person;

    fread(&person,sizeof(struct personalInfo),1,fid);
    person.salary[0]=47500;
    person.salary[1]=40000;
    person.salary[2]=23000;
    person.salary[3]=51000;
    person.salary[4]=37000;
    person.age = 36;

    fseek(fid,2*sizeof(struct personalInfo),SEEK_CUR);
    fwrite(&person,sizeof(struct personalInfo),1,fid);
    fseek(fid,-sizeof(struct personalInfo),SEEK_CUR);
    fread(&person,sizeof(struct personalInfo),1,fid);
    printPerson(&person);
    fclose(fid);

	// while not end of file

	// read a values in a line

	// print the values to the screen 

}