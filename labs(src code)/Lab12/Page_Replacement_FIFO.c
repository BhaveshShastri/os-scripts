// C program for FIFO Page Replacement Algorithm
#include <stdio.h>

int main()
{
    int incomingStream[] = {4, 1, 2, 4, 5};
    int pageFaults = 0, frames = 3;
    int pages = sizeof(incomingStream) / sizeof(incomingStream[0]);
    int temp[frames], pos = 0;

    // Initialize frames to -1 (indicating empty slots)
    for (int i = 0; i < frames; i++)
        temp[i] = -1;

    printf("Incoming \t Frame 1 \t Frame 2 \t Frame 3\n");

    for (int i = 0; i < pages; i++)
    {
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frames; j++)
        {
            if (temp[j] == incomingStream[i])
            {
                found = 1;
                break;
            }
        }

        // If not found, replace the oldest page using FIFO logic
        if (!found)
        {
            temp[pos] = incomingStream[i];  // Replace oldest page
            pos = (pos + 1) % frames;      // Move position in a circular manner
            pageFaults++;
        }

        // Print current frame status
        printf("%d\t\t", incomingStream[i]);
        for (int j = 0; j < frames; j++)
        {
            if (temp[j] != -1)
                printf(" %d\t\t", temp[j]);
            else
                printf(" - \t\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}
