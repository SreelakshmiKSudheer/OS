#include <stdio.h>

#define MAX 3
#define NILL -99999999

int frame[MAX];

void initialize() {
    for (int i = 0; i < MAX; i++)
        frame[i] = NILL;
}

int full() {
    for (int i = 0; i < MAX; i++) {
        if (frame[i] == NILL)
            return 0;
    }
    return 1;
}

void display(int found) {
    for (int j = 0; j < MAX; j++) {
        if (found)
            break;
        if (frame[j] == NILL)
            printf(" ");
        else
            printf("%d ", frame[j]);
    }
    printf("\n");
}

void mfu(int ref[], int n) {
    int faults = 0, current, found;
    int frequency[MAX], lastUse[MAX];

    for (int i = 0; i < MAX; i++) {
        frequency[i] = 0;
        lastUse[i] = -1;
    }

    initialize();

    printf("\n\nMFU\n");
    for (int i = 0; i < n; i++) {
        int index = 0;
        current = ref[i];
        found = 0;

        for (int j = 0; j < MAX; j++) {
            if (frame[j] == current) {
                found = 1;
                frequency[j]++;
                lastUse[j] = i;
                break;
            }
            if (frequency[j] > frequency[index])
                index = j;
        }

        if (!found) {
            faults++;
            if (full()) {
                frame[index] = current;
                frequency[index] = 1;
                lastUse[index] = i;
            } else {
                for (int k = 0; k < MAX; k++) {
                    if (frame[k] == NILL) {
                        index = k;
                        break;
                    }
                }
                frame[index] = current;
                frequency[index] = 1;
                lastUse[index] = i;
            }
        }
        printf("%d : \t", current);
        display(found);
    }
    printf("No. of page faults : %d\n\n", faults);
}

int main() {
    int N, i;

    printf("How many pages in reference string: ");
    scanf("%d", &N);

    const int n = N;
    int ref[n];

    // read reference string 
    printf("Enter the reference string: \n");
    for (i = 0; i < n; i++) {
        scanf(" %d", &ref[i]);
    }

    mfu(ref, n);

    return 0;
}
