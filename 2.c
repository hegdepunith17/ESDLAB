// 2 set 5 th bit 
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
int value;
if (argc> 1)
{
value = atoi(argv[1]);
value |= (1<<5);
printf ("value = %d \n", value);
//}
return 0;
}
