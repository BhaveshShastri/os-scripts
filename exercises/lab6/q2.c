#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 2  // Adjust based on system resources
#define CHUNK_SIZE 1024  // Bytes each thread reads

typedef struct {
    FILE* file;
    long start;
    long end;
    int word_count;
} ThreadData;

pthread_mutex_t lock;
int total_word_count = 0;

int count_words(const char* buffer, size_t size) {
    int count = 0, in_word = 0;
    for (size_t i = 0; i < size; i++) {
        if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

void* process_chunk(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    fseek(data->file, data->start, SEEK_SET);

    char buffer[CHUNK_SIZE];
    size_t bytes_read = fread(buffer, 1, data->end - data->start, data->file);
    data->word_count = count_words(buffer, bytes_read);

    pthread_mutex_lock(&lock);
    total_word_count += data->word_count;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    FILE* file = fopen("large_text.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    long chunk_size = file_size / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].file = file;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? file_size : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, process_chunk, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    fclose(file);

    printf("Total word count: %d\n", total_word_count);
    return 0;
}

