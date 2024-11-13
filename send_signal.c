/**
 * File: send_signal.c
 * Modified by: Holden Truman
 * 
 * Brief summary of program: Generates a random number seeded by time()
 * then ask the user for a process ID to send that random number to
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main() {
    pid_t pid;

    srand(time(NULL)); //random seed
    int value = rand();

    // Get the PID of the receiver program
    printf("Enter the PID of the receiver program: ");
    scanf("%d", &pid);

    union sigval sig_value;
    sig_value.sival_int = value;

    // Send the SIGUSR1 signal with the sival_int value using sigqueue
    sigqueue(pid, SIGUSR1, sig_value);

    return 0;
}
