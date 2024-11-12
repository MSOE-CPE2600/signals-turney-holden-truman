/**
 * File: signal_alarm.c
 * Modified by: Holden Truman
 * 
 * Brief summary of program: After program initializes it waits five seconds to receive an alarm, then
 * prints that it received the alarm. The program doesn't close unless it is terminated/killed
 * by the user.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGALRM
void handle_alarm(int sig) {
    // Print when the alarm signal is received
    printf("Signal received: SIGALRM\n");
}

int main() {
    // Set up the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);
    // Schedule an alarm to go off in 5 seconds
    alarm(5);
    // Wait indefinitely, allowing the program to catch the signal
    while(1) {
        sleep(1);  // Keep the program open
    }
    return 0;
}
