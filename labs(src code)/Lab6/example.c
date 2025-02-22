#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define num_threads 5  // Define the number of threads

// Function to be executed by each thread
void *print_message(void *thread_id) {
    long tid = *((int*) thread_id);  // Dereference the pointer safely
    printf("Thread %ld: Hello from thread!\n", tid);
    sleep(1); // Simulating some work
    printf("Thread %ld: Exiting...\n", tid);
    
    free(thread_id);  // Free allocated memory
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[num_threads]; // Array to hold thread IDs

    for (int i = 0; i < num_threads; i++) {
        int *thread_id = malloc(sizeof(int)); // Allocate memory for thread ID
        if (thread_id == NULL) {
            perror("Failed to allocate memory");
            exit(1);
        }
        *thread_id = i + 1; // Assign thread ID
        
        int status = pthread_create(&threads[i], NULL, print_message, (void*)thread_id);
        if (status) {
            printf("Error creating thread %d, return code: %d\n", i, status);  // Fixed printf
            exit(-1);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

