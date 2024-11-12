/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */
//gcc signal_handler.c -o signal_handler
/**
 * Modified by: Holden Truman
 * 
 * Brief summary of modifications:
 * Removed exit(1) from signal handler, so program doesn't exit when SIGINT is received (Ctrl+C)
 * To Kill the program I ran $ kill -SIGKILL 367040 in the terminal, where I got the pid from $ ps all
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and continues (exit removed)
 */
void handle_signal() {
    printf("Received a signal\n");
    //exit(1);
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}