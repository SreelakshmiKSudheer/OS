#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5

int buffer[MAX];
int empty = MAX, full = 0, semaphore = 0;
int in = -1, out = -1;