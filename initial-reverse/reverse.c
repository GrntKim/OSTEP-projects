#include "string_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

FILE* open_file(char* filepath, char* rw_flag);
int are_identical_files(char* file1, char* file2); 
void reverse(FILE* src, FILE* dest);

int main(int argc, char** argv) {
	switch(argc) {
		case 1:
			reverse(stdin, stdout);
			break;
		case 2:
			reverse(open_file(argv[1], "r"), stdout);
			break;
		case 3:
			if (are_identical_files(argv[1], argv[2])) {
				fprintf(stderr, "reverse: input and output file must differ\n");
				exit(1);
			} else
				reverse(open_file(argv[1], "r"), open_file(argv[2], "w"));
			break;
		default:
			fprintf(stderr, "usage: reverse <input> <output>\n");
			exit(1);
			break;
	}

	return 0;
}

FILE* open_file(char* filepath, char* rw_flag) {
	FILE* fp;
	if((fp = fopen(filepath, rw_flag)) == NULL) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", filepath);
		exit(1);
	}
	return fp;
}

int are_identical_files(char* file1, char* file2) {
	struct stat st1, st2;
	if (stat(file1, &st1) == -1) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", file1);
		exit(1);
	}
	if (stat(file2, &st2) == -1) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", file2);
		exit(1);
	}

	return (st1.st_dev == st2.st_dev) && (st1.st_ino == st2.st_ino);
}

void reverse(FILE* src, FILE* dest) {
	int i;
	char* buffer = NULL;
	size_t len = 0;
	string_vector* sv = init_vector();

	if (sv == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

	while((getline(&buffer, &len, src)) != -1)
		push_back(sv, buffer);

	for(i = (int)sv->size - 1; i >= 0; i--)
		fprintf(dest, "%s", sv->arr[i]);

	if (src != stdin) fclose(src);
	fclose(dest);
	free(buffer);
	free_vector(sv);
}
