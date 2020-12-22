#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    char * info = "./sender";
    char * processed = "./reciever";
    int inf = open(info, O_RDONLY);
    int proc = open(processed, O_WRONLY);
    
    char buffer[256];
    while (1) {
        read(inf, buffer, 256);
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
        char *token;
        char *p = buffer;
        int total = 0;
        while (p) {
            token = strsep(&p, " ");
            total += atoi(token);
        }
        sprintf(buffer, "%d", total);
        write(proc, buffer, sizeof(buffer)); 
    }
    close(inf);
    close(proc);
    unlink(info);
    unlink(processed);
    return 0;
}
