#include <stdio.h>
#include<fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main ()
{
  char* c;
  int n;
  int fin, fout;
  fin = open ("out.txt", O_RDONLY|O_CREAT,0777);
fout = open ("out1.txt", O_WRONLY|O_CREAT,0777);
while(read (fin, &c, 1)==1)
  write (fout, &c, 1);
return 0;
}
