#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        char error_message[] = "Error: Invalid number of arguments";
        write(STDOUT_FILENO, error_message, strlen(error_message));
        write(stderr, "Error: Invalid number of arguments, expected 2\n");
        return 1;
    }


    const char* filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Could not open file");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    off_t size = st.st_size;
    char str[100];
    sprintf(str, "%ld", size);
    write(STDOUT_FILENO, str, strlen(str));

    close(fd);
    return 0;
}
