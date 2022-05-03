
// 1 bit 
#include <stdio.h>
int
main ()
{
  int a = 7;
  int b = 3;
printf ("\n The value of a AND b: %d \n", a & b);
printf ("\n The value of a OR b: %d \n", a | b);
printf ("\n The value of a XOR b: %d \n", a ^ b);
printf ("\n The value of ~a: %d \n", ~a);
printf ("\n The value of a>>1: %d \n", a >> 1);
printf ("\n The value of a>>2: %d \n", a >> 2);
printf ("\n The value of b<<1: %d \n", b << 1);
printf ("\n The value of b<<2: %d \n", b << 2);
}


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

// 3rd read and display
 #include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{int data=0;
char letters[50];
int input;
input = read(0,letters,50);
printf("%d \n", input);
write(1,letters,input);
return(0);
}

// 4th read from out and add to out1 another file
  
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

//keyboard and echo into monitor and also text file  
#include<fcntl.h>
#include <unistd.h>
int main ()
{
  char c[50];
  int n;
  int f1
f1 = open ("out.txt", O_RDWR | O_CREAT, 0777);
    n =  read (0, c, 50);
      write(1,c,n);
      write (f1, c, n); 
  close(f1);
  return 0;
}
  
// fork
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {

   fork(); 
   printf("Fork testing code\n");
   return 0;
}
  
//   pid 
  #include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int
main (void)
{
  pid_t pid;
  char *message;
  int no, NO1 = 1;
  int i, l;
  printf ("calling fork \n");
  pid = fork ();
 
   switch (pid)
    {
    case -1:
      printf ("fork failed \n");
      exit (1);

    case 0:
      message = "Child Process";
      i = 1;
      no = getpid ();
      NO1 = getppid ();
      break;
      
    default:
      message = "Parent Process";
      i = 1;
      no = getpid ();
      NO1 = getppid ();
      break;
    }

    if(pid !=0) {
    printf("HP: hello from parent\n");
        wait(NULL);
        printf("CT: child has terminated\n");
    }

  for (l = i; l > 0; l--)
    {
      puts (message);
      printf ("My ID is %d \n", no);
      printf ("My parent ID is %d \n", NO1);
          }
  return (0);
}

  
  //signal
  
//   1.
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

  
//   2.
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

  
  //multithreading
  #include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

void *read_thread (void *arg)
{
  while (strncmp ("stop", buffer, 4) != 0)
    {
      printf ("Enter text:  ");
      fgets (buffer, BUFFER_SIZE, stdin);
      sleep (1);
    }

  pthread_exit ("read_thread exit successful");
}

void *convert_thread ()
{
  int i;
  while (strncmp ("stop", buffer, 4) != 0)
    {
      sleep (1);
      printf ("Converted text:  ");
      for (i = 0; i < strlen (buffer); i++)
	printf ("%c", toupper (buffer[i]));
    }
  pthread_exit ("convert_thread exit successful");
}

int main ()
{
  int result;
  pthread_t rthread, cthread;
  void *thread_result;
  printf("Enter text, the program will convert it into upper case, \n To stop enter 'stop' \n");
  pthread_create (&rthread, NULL, read_thread, NULL);
  pthread_create (&cthread, NULL, convert_thread, NULL);

  pthread_join (rthread, &thread_result);
  printf("read_thread joined, %s\n",(char *)thread_result);
  pthread_join(cthread, &thread_result);
  printf ("convert_thread joined, %s\n", (char *) thread_result);
return(0);
}

  
  
//   semap
  #include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 1024
sem_t sem;
char buffer[BUFFER_SIZE];

void *read_thread(void *arg)
{
while(strncmp("stop",buffer,4) != 0)
{
printf("Enter text:  ");
fgets(buffer, BUFFER_SIZE, stdin);
sem_post(&sem);
printf("%d \n",sem);
sleep(2);

}

pthread_exit("read_thread exit successful");
}

void *convert_thread()
{
int i;
sem_wait(&sem);
while(strncmp("stop", buffer, 4) != 0)
{
printf("Converted text:  ");
for(i=0; i<strlen(buffer); i++)
printf("%c", toupper(buffer[i]));
sem_wait(&sem);
}
pthread_exit("convert_thread exit successful");
}

int main()
{
int result;
pthread_t rthread, cthread;
void *thread_result;
sem_init(&sem, 0, 1);
printf("Enter text, the program will convert it into upper case, \n To stop enter 'stop' \n");
pthread_create(&cthread, NULL, convert_thread, NULL);

pthread_create(&rthread, NULL, read_thread, NULL);

result = pthread_join(rthread, &thread_result);

printf("read_thread joined, %s\n",(char *)thread_result);

pthread_join(cthread, &thread_result);

printf("convert_thread joined, %s\n",(char *)thread_result);
sem_destroy(&sem);
exit(0);
}

