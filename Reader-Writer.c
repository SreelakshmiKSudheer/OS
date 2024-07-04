#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int *mutex;        //  ensure mutual exclusion when the variable read_count is updated
int *rw_mutex;     // mutual exclusion of reader and writer semaphores
int read_count = 0;    // keeps track of the no. of readers
int shr = 0;       // shared resource

void wait_s(int *semaphore)
{
    while(*semaphore <= 0);
    // do nothing
    *semaphore--;
}

void signal_s(int *semaphore)
{
    *semaphore++;
}

void writer(void *arg)
{
    int writer_id = *((int*)arg);       // writer_id given as the function parameter

    while(1)
    {
        wait_s(&rw_mutex);              // waits if some reader or writer is currently accessing the shared resource
        // if no others access shared resource
        shr++;                          // increment/change shr
        printf("Writer %d: Wrote data %d",writer_id,shr);

        signal_s(&rw_mutex);            // after write allow other readers or writer to access shr
    }
}

void reader(void *arg)
{
    int reader_id = *((int*)arg);       // reader_id given as the function parameter

    while(1)
    {
        wait_s(&mutex);                 // wait if any other readers are updating read_count
        read_count++;                   // increment read_count
        
        /*if this is the first reader(read_count = 1), 
            request lock 
                if rw_mutex > 0 meaning some writer is currently writing (this is the first reader, so no other readers)
                    - request lock is held, waits till access allowed
        */
        if(read_count == 1)
            wait_s(&rw_mutex);
        signal_s(&mutex);

        printf("Reader %d: reads %d\n",reader_id,shr);

        wait_s(&mutex);         // if some reader is accessing read_count, wait
        read_count--;           // decrement read_count
        /*
        if this is the last reader it should ensure that any other writer who is waiting to write should be allowed enter critical section*/
        if(read_count == 0)
            signal_s(&rw_mutex);
        signal_s(&mutex);       // read_count made accessible to other readers
        sleep(1);
    }
}