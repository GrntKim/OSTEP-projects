#include <stdio.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv) {
    if (argc < 2)
        return 0;

    int i;
    FILE* fd;
    char buffer[BUFFER_SIZE];

    for (i = 1; i < argc; i++) {
        if ((fd = fopen(argv[i], "r")) == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        }

        while (fgets(buffer, BUFFER_SIZE, fd)) 
            printf("%s", buffer);
    }

    fclose(fd);
    return 0;
}
