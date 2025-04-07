//Exercise 1: Implement LRU & Optimal
#include <stdio.h>

#define MAX 100

// Function to check if a page exists in frames
int isHit(int frame[], int page, int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == page)
            return 1;
    }
    return 0;
}

// Function to find LRU index
int findLRU(int time[], int frames) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frames; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

// LRU Page Replacement
void lru(int pages[], int n, int frames) {
    int frame[frames], time[frames], counter = 0, faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("\nLRU Page Replacement:\n");
    printf("Incoming\t");
    for (int i = 0; i < frames; i++) printf("Frame %d\t", i + 1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t", pages[i]);

        if (!isHit(frame, pages[i], frames)) {
            int j;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    time[j] = counter++;
                    break;
                }
            }

            if (j == frames) {
                int pos = findLRU(time, frames);
                frame[pos] = pages[i];
                time[pos] = counter++;
            }

            faults++;
        } else {
            for (int j = 0; j < frames; j++) {
                if (frame[j] == pages[i])
                    time[j] = counter++;
            }
        }

        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d\t\t", frame[j]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", faults);
}

// Find the position to replace in Optimal
int predict(int pages[], int frame[], int n, int index, int frames) {
    int result = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }

        // If page not found in future
        if (j == n)
            return i;
    }

    return (result == -1) ? 0 : result;
}

// Optimal Page Replacement
void optimal(int pages[], int n, int frames) {
    int frame[frames], faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    printf("Incoming\t");
    for (int i = 0; i < frames; i++) printf("Frame %d\t", i + 1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t", pages[i]);

        if (!isHit(frame, pages[i], frames)) {
            int j;
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    break;
                }
            }

            if (j == frames) {
                int pos = predict(pages, frame, n, i + 1, frames);
                frame[pos] = pages[i];
            }

            faults++;
        }

        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d\t\t", frame[j]);
            else
                printf("-\t\t");
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", faults);
}

// Main Function
int main() {
    int pages[] = {4, 1, 2, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
