#include <stdio.h>

int main(int argc, char** argv) {
    int i;
    FILE* fd;
    int count = 0;
    char ch, last_ch = 0;

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if ((fd = fopen(argv[i], "r")) == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }

        while ((ch = fgetc(fd)) != EOF) {
            if (!count) {
                last_ch = ch;
                count = 1;
            } else if (ch == last_ch) {
                count++;
            } else {
                fwrite(&count, sizeof(count), 1, stdout);
                putchar(last_ch);
                count = 1;
                last_ch = ch;
            }
        }
        fclose(fd);
    }

    if (count > 0) {
        fwrite(&count, sizeof(count), 1, stdout);
        putchar(last_ch);
    }

    return 0;
}
