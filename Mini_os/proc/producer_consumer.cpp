#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10


typedef struct {
    int buffer[BUFFER_SIZE];
    // index where producer will write item
    size_t in;
    // index where consumer will read item
    size_t out;
    // binary semaphores
    sem_t mutex;
    sem_t empty;
    sem_t full;
} semaphore_t;

// Initialize the semaphore
void semaphore_init(semaphore_t *semaphore) {
    semaphore->in = 0;
    semaphore->out = 0;
    // initially mutex is unlocked
    sem_init(&semaphore->mutex, 0, 1);
    // all buffers are empty initially
    sem_init(&semaphore->empty, 0, BUFFER_SIZE);
    // no buffer is full
    sem_init(&semaphore->full, 0, 0);
}

// produce an item
void *producer(void *arg) {
    // typecast arg to semaphore_t
    semaphore_t *semaphore = (semaphore_t *) arg;
    for (int i = 0; i < 10; i++) {
// if sem empty=0, wait
        sem_wait(&semaphore->empty);
        // wait if consumer is consuming
        sem_wait(&semaphore->mutex);
        // write item into buffer
        semaphore->buffer[semaphore->in] = i;
        printf("Produce %d at %zu\n", i, semaphore->in);
        semaphore->in = (semaphore->in + 1) % BUFFER_SIZE;

        // release mutex, allow threads to access buffer
        sem_post(&semaphore->mutex);
        // This signals to any waiting consumers
        // that there is a new item in the buffer that they can consume.
        sem_post(&semaphore->full);
    }
    return NULL;
}


void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        semaphore_t *semaphore = (semaphore_t *) arg;
        // if sem full > 0, decrement, if 0 wait until producer add an item
        sem_wait(&semaphore->full);
        sem_wait(&semaphore->mutex);
        // consume an item
        int item = semaphore->buffer[semaphore->out];
        semaphore->out = (semaphore->out + 1) % BUFFER_SIZE;
        printf("Consumed %d at %zu\n", item, semaphore->out);

        // release semaphores
        sem_post(&semaphore->mutex);
        // signals that there's an empty slot available
        sem_post(&semaphore->empty);
    }
    return NULL;
}

int main() {
    semaphore_t semaphore;
    semaphore_init(&semaphore);  // Initialize the semaphore

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, &semaphore);  // Create the producer thread
    pthread_create(&consumer_thread, NULL, consumer, &semaphore);  // Create the consumer thread

    pthread_join(producer_thread, NULL);  // Wait for the producer thread to finish
    pthread_join(consumer_thread, NULL);  // Wait for the consumer thread to finish

    sem_destroy(&semaphore.mutex);  // Destroy the mutex semaphore
    sem_destroy(&semaphore.empty);  // Destroy the empty semaphore
    sem_destroy(&semaphore.full);  // Destroy the full semaphore
    sleep(1);

    return 0;
}