#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t writer;
pthread_mutex_t reader_mutex;
int reader_count = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    pthread_mutex_lock(&reader_mutex);
    reader_count++;
    if(reader_count == 1) {
        sem_wait(&writer);
    }
    pthread_mutex_unlock(&reader_mutex);

    printf("Reader %d is reading...\n", id);
    sleep(1);
    printf("Reader %d has finished reading.\n", id);

    pthread_mutex_lock(&reader_mutex);
    reader_count--;
    if(reader_count == 0) {
        sem_post(&writer);
    }
    pthread_mutex_unlock(&reader_mutex);
    return NULL;
}

void* writer_func(void* arg) {
    int id = *(int*)arg;
    sem_wait(&writer);
    printf("Writer %d is writing...\n", id);
    sleep(1);
    printf("Writer %d has finished writing.\n", id);
    sem_post(&writer);
    return NULL;
}

int main() {
    int num_readers, num_writers;
    printf("Enter number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter number of writers: ");
    scanf("%d", &num_writers);

    sem_init(&writer, 0, 1);
    pthread_mutex_init(&reader_mutex, NULL);

    pthread_t readers[num_readers], writers[num_writers];
    int ids[num_readers > num_writers ? num_readers : num_writers];

    for(int i = 0; i < num_readers; i++) {
        ids[i] = i+1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for(int i = 0; i < num_writers; i++) {
        ids[i] = i+1;
        pthread_create(&writers[i], NULL, writer_func, &ids[i]);
    }

    for(int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    for(int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&writer);
    pthread_mutex_destroy(&reader_mutex);

    return 0;
}
