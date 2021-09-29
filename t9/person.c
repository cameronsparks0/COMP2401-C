// FILE is person.c

/************************************************/
// INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "mystat.h"

/************************************************/
// DEFINE

#define BASE_SALARY 30000


/************************************************/

/* Print the information of a person.

   input
   p - a person record

*/

void print(PersonRec *p)
{
    float avg_best_five_years = 0;


    average(p->salary, NUM_YEARS, &avg_best_five_years);


    printf("Person Name: %-10s %-10s, Age: %hu, Best five years salary: %6.2f\n",
            p->first_name, p->last_name, p->age, avg_best_five_years);
}

/************************************************/

/* Populate the information of a person.

   input
   p - a person record

*/

void populate(PersonRec *p) {

    int i;
    static long long id = 0;
    char *first_name[5] = { "David", "John", "Diana", "Rob", "Sarah" };
    char *last_name[5] = { "Smith", "Bell", "West", "Johnson", "Ford" };

    strncpy(p->last_name, last_name[rand() % 5], NAME_LENGTH);
    strncpy(p->first_name, first_name[rand() % 5], NAME_LENGTH);

    p->id = id++;
    p->age = (rand() % 45) + 20;

    // Populate the salary information.
    for (i = 0; i < NUM_YEARS; i++) {
        p->salary[i] = BASE_SALARY + (rand() & 5000);
    }
}

/************************************************/

/* Compare based on age

   input
   p1, p2 - pointer to a person record
   return - 1 if age of p1 is bigger than p2
            -1 if age of p2 is bigger than p1
            0 if age of p1 and p2 are the same
*/

int compareAge(const void *p1, const void *p2) {
   struct person *n1 = (struct person*)p1;
   struct person *n2 = (struct person*)p2;

   if (n1->age < n2->age) return -1;
   if (n1->age > n2->age) return 1;
   return 0;
}

/************************************************/

/* Compare based on average salary

   input
   p1, p2 - pointer to a person record

   return - -1 if average salary of p1 is bigger than p2
            1 if average salary of p2 is bigger than p1
            0 if average salary of p1 and p2 are the same
*/

int compareSalary(const void *p1, const void *p2) {
   struct person *n1 = (struct person*)p1;
   struct person *n2 = (struct person*)p2;

   float salary1, salary2;
   average(n1->salary,NUM_YEARS,&salary1);
   average(n2->salary,NUM_YEARS,&salary2);

   if (salary1 < salary2) return -1;
   if (salary1 > salary2) return 1;
   return 0;

  // put your code here
  
}

/************************************************/

/* Compare based on last name

   input
   p1, p2 - pointer to a person record
   return - 1 if last name of p1 is alphabatically before that of p2
            -1 if last name of p2 is alphabatically before that of p1
            0 if last name of p1 is the same as that of p2
*/

int compareLastName(const void *p1, const void *p2) {
   struct person *n1 = (struct person*)p1;
   struct person *n2 = (struct person*)p2;

   return(strcmp(n1->last_name,n2->last_name));

  // put your code here
 
}

