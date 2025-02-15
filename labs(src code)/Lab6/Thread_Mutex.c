#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
int shared_counter = 0;
pthread_mutex_t lock;  // Mutex variable

void* increment_counter(void* tid) {
    pthread_mutex_lock(&lock);  // Lock before modifying shared resource
    shared_counter++;
    printf("Thread %ld incremented counter to %d\n", (long)tid, shared_counter);
    pthread_mutex_unlock(&lock);  // Unlock after modification
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);  // Initialize mutex

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);  // Destroy mutex after use
    printf("Final counter value: %d\n", shared_counter);
    return 0;
}

