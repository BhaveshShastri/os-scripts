#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5  // Number of threads to create

// Function to be executed by each thread
void *print_message(void *thread_id) {
    long tid = (long) thread_id;
    printf("Thread %ld: Hello from thread!\n", tid);
    sleep(1); // Simulating some work
    printf("Thread %ld: Exiting...\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int status;
    long i;

    // Creating multiple threads
    for (i = 0; i < NUM_THREADS; i++) {
        printf("Main: Creating thread %ld\n", i);
        status = pthread_create(&threads[i], NULL, print_message, (void *)i);

        if (status) {
            printf("Error creating thread %ld, return code: %d\n", i, status);
            exit(-1);
        }
    }

    // Waiting for all threads to complete
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: All threads completed. Exiting program.\n");
    return 0;
}

