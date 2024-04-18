#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int fd = open("data.txt", O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file.\n");
        return -1;
    }


    // get size of file using fstat
    struct stat st;
    if (fstat(fd, &st) == -1) {
        close(fd);
        perror("Error getting file size");
        return -1;
    }

    int num_elements = st.st_size / sizeof(int);

    int *map = mmap(NULL, st.st_size , PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        return -1;
    }

    printf("Before updating...\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%d ", map[i]);
    }
    // multiply data in mapped region with 2
    for (int i = 0; i < num_elements; i++) {
        map[i] = map[i] * 2;
    }
    printf("\nAfter updating data...\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%d ", map[i]);
    }
    printf("\n");

    // sync changes on disk
    if (msync(map, st.st_size, MS_SYNC) == -1) {
        perror("Error syncing file to disk.\n");
    }

    // free mapped region
    if (munmap(map, st.st_size) == -1) {
        perror("Error un-mapping.\n");
    }

    close(fd);

    return 0;
}
