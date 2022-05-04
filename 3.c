#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
int data=0;
char letters[50];
int input;
input = read(0,letters,50);
printf("%d \n", input);
write(1,letters,input);
return(0);
}
