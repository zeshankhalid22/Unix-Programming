#include <stdio.h>
#include "stdlib.h"
#include <pthread.h>

// data to be sorted by particular array
typedef struct {
    int *array;
    int start;
    int end;
} SortData;

// merge two sorted subArrays
void merge(int *array, int start, int mid, int end) {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    // Create temp arrays
    int *L = (int *) malloc(n1 * sizeof(int));
    int *R = (int *) malloc(n2 * sizeof(int));

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = array[start + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    // Merge the temp arrays back into array[start..end]
    i = 0; // index of first subArray
    j = 0;  // index of second subArray
    k = start;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
    // Free memory
    free(L);
    free(R);
}

void mergeSort(int *array, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        // recursively break array into half
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);

        // merge left and right part
        merge(array, start, mid, end);
    }
}

void *sortThread(void *arg) {
    // type casting
    SortData *data = (SortData *) arg;
    printf("Thread %lu is sorting from index %d to %d\n",
           pthread_self(), data->start, data->end);
    mergeSort(data->array, data->start, data->end);
}

int main() {
    int arraySize = 20;
    int numThreads = 4;
    // work to be done by each thread
    int threadWork = arraySize / numThreads;

    int *array = malloc(arraySize * sizeof(int));
    // populate array with random numbers
    srand(time(NULL));
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand() % 100 + 1;
    }
    printf("Before Sort\n");
    for(int i=0;i<arraySize;i++) {
        printf("%d ",array[i]);
    }
    printf("\n");


    // allocate parameters to pass for each thread
    SortData *data = malloc(numThreads * sizeof(SortData));
    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));


    // Determine the range of indices for each thread
    for (int i = 0; i < numThreads; i++) {
        data[i].array = array;
        data[i].start = i * threadWork;
        data[i].end = (i + 1) * threadWork;
        pthread_create(&threads[i], NULL, sortThread, &data[i]);
    }

    // Wait for all threads to finish.
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge the sorted subarrays.
for (int i = 1; i < numThreads; i++) {
    int start = data[0].start;
    int mid = data[i - 1].end;
    int end = data[i].end;
    merge(array, start, mid, end);
    data[0].end = end; // Update the end for the next merge
}

    printf("After Sort\n");
    for(int i=0;i<arraySize;i++) {
        printf("%d ",array[i]);
    }
    printf("\n");

    free(array);
    free(data);
    free(threads);

}
