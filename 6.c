#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void my_handler(int signal)
{
printf("Problem encountered %d \n", signal);
}
int main()
{
(void) signal (SIGINT,my_handler);
while(1)
{
printf("Hello \n");
sleep(2);
}
}

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
(void) signal (SIGINT,SIG_IGN);
while(1)
{
printf("%d \n", getpid());
sleep(1);
}
}
