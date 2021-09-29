//file find_struct.c

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define MAX_EMPLOYEES  30
#define NAME_SIZE     16
#define NUM_NAMES 7

struct emp{
    char firstName[NAME_SIZE];
    char familyName[NAME_SIZE];
    float salary;
    float yearsWithCompany;
};


// This is a forward reference
void populateEmployee(struct emp *emp);
int cmpEmployee(struct emp *emp, char *familyName);

int myStrCmp(char *s1, char *s2){
    if (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) 
    {
        return(myStrCmp(++s1, ++s2));
        
    }
    if (*s1 < *s2) {
        return(-1);
    }
    else {
        return (*s1 > *s2);
    }
}

int main(int argc, char* argv[])
{
        struct emp empArr[MAX_EMPLOYEES];
        struct emp *empPtrArr[MAX_EMPLOYEES];

        int i;

	// initialize each element of empPtrArr to point to corresponding element of empArr.  
	
        for (i = 0; i < MAX_EMPLOYEES; i++) {
            empPtrArr[i] = &empArr[i];
		// ADD CODE
	}
	
	// populate the employee array
	for (i = 0; i < MAX_EMPLOYEES; i++) {
        populateEmployee(empPtrArr[i]);

	}
	
	// print the family name
	for (i = 0; i < MAX_EMPLOYEES; i++) printf("%s\n", empPtrArr[i]->familyName);



	// add code to search for employee against the family name "Carp"
    char *temp = "Carp";
    for (i = 0; i < MAX_EMPLOYEES; i++) {
        if(cmpEmployee(empPtrArr[i],temp)==1){
            printf("------------\n");
            printf("Found Record!\n");
            printf("First Name: %s\n",empPtrArr[i]->firstName);
            printf("Family Name: %s\n",empPtrArr[i]->familyName);
            printf("Salary: %.2f\n",empPtrArr[i]->salary);
            printf("Years: %.2f\n",empPtrArr[i]->yearsWithCompany);
        }

	}

	// if found print the record

	// add code to search for employee against the family name "King"
    temp = "King";
    for (i = 0; i < MAX_EMPLOYEES; i++) {
        if(cmpEmployee(empPtrArr[i],temp)==1){
            printf("------------\n");
            printf("Found Record!\n");
            printf("First Name: %s\n",empPtrArr[i]->firstName);
            printf("Family Name: %s\n",empPtrArr[i]->familyName);
            printf("Salary: %.2f\n",empPtrArr[i]->salary);
            printf("Years: %.2f\n",empPtrArr[i]->yearsWithCompany);
        }

	}

	// if found print the record

       
    return 0;
}





/**************************************************************/
/* Purpose: compare the employee record with respect to family name

Input
emp - an employee record
familyName - the key for searching an employee 

Output
None

Return
0 if the family name in the employee record does not match that of the given key
1 if the family name in the employee record matches that of the given key
*/


int cmpEmployee(struct emp *emp, char *familyName)

{
    if(myStrCmp(emp->familyName,familyName)==0){
        return (1);
    }
    else{
        return 0;
    }
	// add code
	// use the -> operator to access the fields
	// recall the precedence order between "*" and "->" operators


}


/**************************************************************/
/* populate an employee passed in by reference
 
 input/output
 emp - pointer to an emplyee to be initialized
 
 assumption:
 emp has been previously allocated
 */

void populateEmployee(struct emp *emp)
{
    int j;
 
    char *fn[NUM_NAMES] = {"John", "Jane", "David", "Dina", "Justin","Jennifer", "Don"};
    char *sn[NUM_NAMES] = {"Smith", "Johnson", "Mart", "Carp", "Farmer","Ouster","Door"};


    // get a random value and make sure that it is in the range of 0-30000
    emp->salary = rand() % 30000;
    emp->yearsWithCompany = rand() % 30;
    j = rand() % NUM_NAMES;
    strncpy(emp->firstName, fn[j],NAME_SIZE-1);
    j = rand() % NUM_NAMES;
    strncpy(emp->familyName, sn[j],sizeof(emp->familyName)-1);

}
