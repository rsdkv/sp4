
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./program filename\n", 26);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Error: File not found\n", 22);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        write(STDERR_FILENO, "Error: Unable to get file information\n", 39);
        close(fd);
        exit(EXIT_FAILURE);
    }

    char size[20];
    int n = sprintf(size, "%lu\n", st.st_size);
    write(STDOUT_FILENO, size, n);
    close(fd);
    exit(EXIT_SUCCESS);
}