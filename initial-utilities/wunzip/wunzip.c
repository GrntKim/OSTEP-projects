#include <stdio.h>

int main(int argc, char** argv) {
    int i;
    FILE* fd;
    char ch;
    int num = 0;

    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if ((fd = fopen(argv[i], "r")) == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }
        while (fread(&num, sizeof(int), 1, fd) == 1) {
            ch = fgetc(fd);
            while(num--)
                printf("%c", ch);
        }
        fclose(fd);
    }

    return 0;
}
