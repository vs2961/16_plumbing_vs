#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char * sender = "./sender";
    int pipe1 = mkfifo(sender, 0664);

    char * reciever = "./reciever";
    int pipe2 = mkfifo(reciever, 0664);

    int fd1 = open(sender, O_WRONLY);
    int fd2 = open(reciever, O_RDONLY);

    char buffer[256];

    while(1) {
        fgets(buffer, 256, stdin);
        write(fd1, buffer, sizeof(buffer));
        read(fd2, buffer, sizeof(buffer));
        printf("Your sum is: %s\n", buffer);
    }

    close(fd1);
    close(fd2);
    unlink(sender);
    unlink(reciever);

    return 0;
}
