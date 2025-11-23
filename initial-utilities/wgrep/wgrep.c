#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv) {
    int i;
    FILE* fd;
    char* target = argv[1];
    size_t len = 0;
    char* line = NULL;
    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    } else if (argc == 2) {
        while(fgets(buffer, BUFFER_SIZE, stdin))
            if (strstr(buffer, target) != NULL)
                printf("%s", buffer);
    } else {
        for (i = 2; i < argc; i++) {
            if ((fd = fopen(argv[i], "r")) == NULL) {
                printf("wgrep: cannot open file\n");
                return 1;
            }
            while (getline(&line, &len, fd) != -1)
                if (strstr(line, target) != NULL)
                    printf("%s", line);
            fclose(fd);
        }
    }
    if (line) 
        free(line);
    return 0;
}
