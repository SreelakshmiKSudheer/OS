#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

int state[N] = {1, 1, 1, 1, 1};
int self[N] = {0, 0, 0, 0, 0};  // to represent condition variables
/*
states:
1: thinking
2: hungry
3: eating
*/

int mutex = 1;

void wait_s(int *semaphore) {
    while (*semaphore <= 0);
    (*semaphore)--;
}

void signal_s(int *semaphore) {
    (*semaphore)++;
}

void test(int i) {
    if (state[(i+1) % N] != 3 && state[i] == 2 && state[(i+4) % N] != 3) {
        state[i] = 3;
        printf("Philosopher %d is eating\n", i + 1);
        self[i] = 0;  // Philosopher is no longer waiting
    }
}

void pickup(int i) {
    wait_s(&mutex);
    state[i] = 2;  // Philosopher is hungry
    printf("Philosopher %d is hungry\n", i + 1);
    test(i);
    signal_s(&mutex);
    wait_s(&self[i]);  // If unable to eat, wait
}

void drop(int i) {
    wait_s(&mutex);
    state[i] = 1;  // Philosopher is thinking
    printf("Philosopher %d putting fork %d and %d down\n", i + 1, (i + 4) % N + 1, i + 1);
    printf("Philosopher %d is thinking\n", i + 1);
    test((i+1) % N);  // Test if neighbors can eat
    test((i+4) % N);
    signal_s(&mutex);
}

void* philosopher(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sleep(1);  // Philosopher is thinking
        pickup(id);
        sleep(0);  // Philosopher is eating
        drop(id);
    }
    pthread_exit(NULL);
}

int main() {
    int i, id[N];
    pthread_t ph[N];

    for (i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &id[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }

    return 0;
}
