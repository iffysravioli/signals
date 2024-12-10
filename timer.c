/* Extended timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarm_count = 0; // Counts the number of alarms

time_t start_time; // Start time of the program

void alarm_handler(int signum)
{ // SIGALRM handler
    alarm_count++;
    alarm(1); // Schedule the next alarm in 1 second
}

void sigint_handler(int signum)
{ // SIGINT handler
    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);

    printf("\nProgram executed for %.0f seconds.\n", elapsed);
    printf("Number of alarms received: %d\n", alarm_count);
    exit(0); // Exit the program
}

void sigusr1_handler(int signum)
{ // SIGUSR1 handler
    printf("Received SIGUSR1!\n");
}

int main(int argc, char *argv[])
{
    start_time = time(NULL); // Record the start time

    signal(SIGALRM, alarm_handler); // Register SIGALRM handler
    signal(SIGINT, sigint_handler); // Register SIGINT handler
    signal(SIGUSR1, sigusr1_handler); // Register SIGUSR1 handler

    alarm(1); // Schedule the first alarm in 1 second

    while (1)
    {
        pause(); // Wait for any signal to be delivered
    }
    return 0;
}