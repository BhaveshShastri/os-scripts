#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig) {
    printf("Received signal %d. Resuming execution...\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, signal_handler); // Handle Ctrl+C (SIGINT)
    printf("Process PID = %d. Press Ctrl+C to terminate.\n", getpid());
    pause(); // Wait for a signal
    return 0;
}

