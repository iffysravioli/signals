/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t alarm_handled = 0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  alarm_handled = 1;
  alarm(5) ; 
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(5); //Schedule a SIGALRM for 1 second
  while (1)
  {

  
    while (!alarm_handled)
        ;
    
    printf("Turing was right!\n");
    alarm_handled = 0;

  }

  return 0; //never reached
}