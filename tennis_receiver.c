/**
 * File: tennis_receiver.c
 * Modified by: Holden Truman
 * 
 * Brief summary of program: Returns a ball from the sender program.
 * The two programs hit the ball between eachother, and a point is scored when the other side
 * fails to return the ball. The side that score serves next. A side wins when it scores at least
 * 4 points and is leading
 * by atleast 2 points.
 *
 * Program can be run by running the sender and receiver executables in seperate terminals
 * or by running run.sh in one terminal and other_run.sh in another
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int my_points = 0;
int other_points = 0;

// Signal handler for SIGUSR2, winner serves
void handle_serve(int sig, siginfo_t *siginfo, void *context) { 
    my_points++; //server scored
    printf("Receiver Scored\n");
    printf("Receiver %d; Server %d\n", other_points, my_points);
    printf("\n"); //create space

    //send new ball
    srand(time(NULL)); //random seed
    pid_t pid = siginfo->si_pid; //send to pid

    union sigval new_sig_value;
    new_sig_value.sival_int = 0; //hit count is 0
    printf("Receiver Served\n");
    sigqueue(pid, SIGUSR1, new_sig_value);
}



// Signal handler for SIGUSR1
void handle_ball(int sig, siginfo_t *siginfo, void *context) {
    sleep(2);
    srand(time(NULL)); //random seed
    pid_t pid = siginfo->si_pid;

    union sigval new_sig_value;
    new_sig_value.sival_int = siginfo->si_value.sival_int + 1; //increment the value by 1
    if ((rand() % 100) < 60) { //successfully returns ball
        sigqueue(pid, SIGUSR1, new_sig_value);
        printf("Receiver returned ball. Hit #%d\n", new_sig_value.sival_int);
    } else {
        other_points++;
        printf("Receiver Failed to return ball.\n"
        "Receiver %d; Server %d\n", my_points, other_points);
        if (other_points >= 4 && (other_points - my_points) >= 2) {
            //other player won
            printf("Sender Wins\n");
            kill(pid, SIGTERM); //Terminate other
            exit(0);
        } else {
            sigqueue(pid, SIGUSR2, new_sig_value);
        }
        printf("\n"); //create space
    }
}

int main() {
    struct sigaction sa1;
    struct sigaction sa2;

    // Set up the sigaction structure to specify the signal handler
    sa1.sa_flags = SA_SIGINFO;
    sa2.sa_flags = SA_SIGINFO;

    sa1.sa_sigaction = handle_ball;
    sa2.sa_sigaction = handle_serve;
    sigemptyset(&sa1.sa_mask); 
    sigemptyset(&sa2.sa_mask); 

    // Register the signal handler for SIGUSR1 to handle ball
    sigaction(SIGUSR1, &sa1, NULL);
    // Register the signal handler for SIGUSR2 to serve ball
    sigaction(SIGUSR2, &sa2, NULL);

    while (1) {
        pause(); //Run indefinitely
    }

    return 0;
}


