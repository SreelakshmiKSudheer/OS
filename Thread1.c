#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int semaphore = 1; // Initialize semaphore to 1
int n = 1;

void wait(int *semaphore) {
    while (*semaphore <= 0); // Wait until semaphore is positive
    (*semaphore)--; // Decrement semaphore
}

void sig(int *semaphore) {
    (*semaphore)++; // Increment semaphore
}

void *number(void *arg) {
    int no = *((int *)arg); 
    int st = no;
    while (1) {
        wait(&semaphore);
        if (n == st)
        {
            printf("Thread[%d]: %d\n", st, no);
            no += 2;
            n = 3 - st;
        }
            
        
        sig(&semaphore);
    }
}

int main() {
    pthread_t t1, t2;
    int odd = 1, even = 2;
    pthread_create(&t1, NULL, number, &odd); // Pass the address of 'odd'
    pthread_create(&t2, NULL, number, &even); // Pass the address of 'even'

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
