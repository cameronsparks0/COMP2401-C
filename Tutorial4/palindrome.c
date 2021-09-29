#include<stdio.h>
#include<string.h>
#include <math.h>

// This is a forward reference
int palindrome(char *s);

int main() {

  char word[30];

    
  printf ("Enter a word or \"q\" to stop: ");
  scanf ("%s", word);

  while (strcmp(word, "q") != 0) {
    palindrome(word);
    printf ("Enter a word or \"q\" to stop: ");
    scanf ("%s", word);
  };

  return 0;

}
  
int palindrome(char *s)
{

  int maxLength = strlen(s)-1;
  int flag=1;

  for(int x=0; x<=maxLength;x++){
    if(s[x]!=s[maxLength-x]){
      flag=0;
    }
  }

  if(flag==1){
    printf("YOU FOUND A PALINDROME!\n");
    return 1;
  }
  else{
    printf("NOT A PALINDROME!");
    return 1;
  }
  // add code to test for palindrome and print a message  

}
