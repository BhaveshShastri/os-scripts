#include <stdio.h>
#include <pthread.h>

#define SIZE 10  // Size of the array
int arr[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Sample array
int sum1 = 0, sum2 = 0;  // Store sums computed by threads

void* sum_half(void* arg) {
    int index = *(int*)arg;
    int start = (index == 0) ? 0 : SIZE / 2;
    int end = (index == 0) ? SIZE / 2 : SIZE;
    int* result = (index == 0) ? &sum1 : &sum2;

    for (int i = start; i < end; i++) {
        *result += arr[i];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int index1 = 0, index2 = 1;

    // Creating two threads
    pthread_create(&thread1, NULL, sum_half, &index1);
    pthread_create(&thread2, NULL, sum_half, &index2);

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Compute final sum
    int final_sum = sum1 + sum2;
    printf("Final Sum: %d\n", final_sum);

    return 0;
}

