#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main()
{
    int fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    // Open file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read from file
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Display read content
    printf("Bytes read: %zd\n", bytes_read);
    printf("Content: %s\n", buffer);

    // Close file
    close(fd);

    return 0;
}
