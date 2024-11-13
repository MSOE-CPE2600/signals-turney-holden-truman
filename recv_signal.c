/**
 * File: recv_signal.c
 * Modified by: Holden Truman
 * 
 * Brief summary of program: The program runs indefinitely (unless terminated or killed), and if it receives 
 * the SIGUSR1 signal it will print that it received it and the process ID of the sender. The program will
 * still stay open after this, and can continue to receive SIGUSR1 signals. The SA_SIGINFO flag allows
 * the program to receive information about the sender
 * 
 * You can send SIGUSR1 to the process by issuing $  kill -SIGUSR1 <pid> in the terminal
 * Where <pid> comes from ps all
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGUSR1
void handle_sigusr1(int sig, siginfo_t *siginfo, void *context) {
    // Print the sender's process ID
    printf("Received SIGUSR1 with sival_int value: %d\n", siginfo->si_value.sival_int);
}

int main() {
    struct sigaction sa;

    // Set up the sigaction structure to specify the signal handler
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigusr1;
    sigemptyset(&sa.sa_mask); 

    // Register the signal handler for SIGUSR1
    sigaction(SIGUSR1, &sa, NULL);

    while (1) {
        sleep(1); // Suspend the program until a signal is received
    }

    return 0;
}


