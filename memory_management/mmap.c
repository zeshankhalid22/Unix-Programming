#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <glob.h>

#define PAGESIZE 4096

int main() {
    int numPages;
    int fd;

    printf("How many Pages you wanna allocate > ");
    scanf("%d", &numPages);

    // Open a file
    fd = open("data.txt", O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Get the size of the file
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    // Determine the size of the needed mapping
    size_t mappingSize = st.st_size;
    if (mappingSize < numPages * PAGESIZE) {
        mappingSize = numPages * PAGESIZE;
    }

    // Create a mapping in the process's virtual memory space
    char *addr = mmap(NULL, mappingSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (addr == MAP_FAILED) {
        // if We unable to map memory
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("Before Changes > %s\n", addr);
    // move to next digit
    for (int i = 0; i < st.st_size; i++) {
        // changes are happening in mapped region in
        // virtual addresses space
        addr[i] = addr[i]+1;
    }
    printf("After Changes > %s\n", addr);

    // Write any changes made to the mapped memory
    // back to the file on disk
    if (msync(addr, numPages * PAGESIZE, MS_SYNC) == -1) {
        perror("msync");
    }

    // Free up the memory
    if (munmap(addr, numPages * PAGESIZE) == -1) {
        perror("munmap");
    }

    close(fd);

    return 0;
}
