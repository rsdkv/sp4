#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        char error_message[] = "You must use only 1 argument:\n- Amount of symbols to print\n";
        write(STDERR_FILENO,
              error_message,
              strlen(error_message));
        return -1;
    }

    const char *filename = argv[1];
    struct stat st;

    if (stat(filename, &st) == -1) {
        perror("stat");
        exit(1);
    }
    write(STDOUT_FILENO, st.st_size,strlen(st.st_size))
    printf("File size: %ld bytes\n", st.st_size);
    return 0;
}

