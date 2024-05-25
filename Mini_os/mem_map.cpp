#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "include/mem_map.h"

using namespace std;

#define PAGESIZE 4096

void mem_to_file_map() {
    int numPages;
    int fd;

    cout << "How many Pages you wanna allocate > ";
    cin >> numPages;

    // Open a file
    fd = open("../data.txt", O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    // Get the size of the file
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error getting file size");
        close(fd);
        return;
    }

    // Determine the size of the needed mapping
    size_t mappingSize = st.st_size;
    if (mappingSize < numPages * PAGESIZE) {
        mappingSize = numPages * PAGESIZE;
    }

    // Create a mapping in the process's virtual memory space
    void *ret_addr = mmap(NULL, mappingSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Allocated %d pages (%d bytes) from address %p\n", numPages, numPages * PAGESIZE, ret_addr);
    char *addr = static_cast<char *>(ret_addr);

    if (addr == MAP_FAILED) {
        // if We are unable to map memory
        perror("mmap");
        close(fd);
        return;
    }

    cout << "Before Changes: " << addr << endl;
    // move to next digit
    for (int i = 0; i < st.st_size; i++) {
        // changes are happening in mapped region in
        // virtual addresses space
        addr[i] = addr[i] + 1;
    }
    cout << "After changes: " << addr << endl;

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
    cout << endl;
}
