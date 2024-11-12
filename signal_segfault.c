/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Holden Truman
 * 
 * Brief summary of modifications: I added a line to handle the segmentation fault
 * signal that occurs when dereferencing the NULL pointer. When this happens a statement is printed,
 * then the program continues again, and tries to dereference the NULL pointer again, which causes a loop
 * of segmentation fault signal to be received and handled.
 */


#include <stdio.h>
#include <signal.h>

void handle_signal() {
    printf("Segmentation Fault Received\n");
}

int main (int argc, char* argv[]) {
    // Register for the signal
    signal(SIGSEGV, handle_signal);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}