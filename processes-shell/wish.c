#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

#define MAX_ARGS 10
#define MAX_PATH_LEN 1024

const char error_message[30] = "An error has occurred\n";
const char* built_in_cmds[] = { "exit", "cd", "path", NULL };

bool is_builtin(char* cmd);

int main(int argc, char** argv) {
	char* paths = (char*)malloc(MAX_PATH_LEN);
	strcpy(paths, "/bin");
	int i;
	char* input = NULL;
	size_t buffer_size = 0;
	ssize_t nread;
	pid_t rc;
	char* args[MAX_ARGS];
	char *token;
	const char* delimiter =  " ";
	int arg_idx;
	char* inputptr;
	char* full_path = NULL;
	bool found_path;
	FILE* batch;

	if (argc == 2) { 
		if((batch = fopen(argv[1], "r")) == NULL) {
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(1);
		}
	}
	while (1) {
		if (argc == 1)
			printf("wish> ");
		nread = getline(&input, &buffer_size, argc == 2 ? batch : stdin);

		// ctrl + D: exit
		if (nread == -1) { 
			free(input);
			free(paths);
			exit(0);
		}

		if (nread && input[nread - 1] == '\n')
			input[nread - 1] = '\0';

		if (input[0] == '\0') continue;

		inputptr = input;
		arg_idx = 0;
		while ((token = strsep(&inputptr, delimiter)) != NULL && 
				arg_idx < MAX_ARGS - 1)
			if (*token != '\0')
				args[arg_idx++] = token;            
		args[arg_idx] = NULL;

		if (is_builtin(args[0])) {
			if (strcmp(args[0], "exit") == 0) {
				free(input);
				free(paths);
				exit(0);
			}
			else if (strcmp(args[0], "cd") == 0) {
				if (arg_idx != 2) {
					write(STDERR_FILENO, error_message, strlen(error_message));
				} else {
					if(chdir(args[1]) != 0) 
					write(STDERR_FILENO, error_message, strlen(error_message));
				}
			} else if (strcmp(args[0], "path") == 0) {
				if (paths != NULL) free(paths);
				paths = (char*)malloc(MAX_PATH_LEN);
				if (paths == NULL) {
					write(STDERR_FILENO, error_message, strlen(error_message));
					exit(1);
				}
				if (arg_idx == 1) {
					continue;
				} else {
					paths[0] = '\0';
					for (i = 1; i < arg_idx; i++) {
						if (i > 1) strcat(paths, ":");
						strcat(paths, args[i]);
					}
				}
			}
		} else if (arg_idx) {
			found_path = false;
			full_path = malloc(MAX_PATH_LEN);
			if (full_path == NULL) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}
			char* paths_copy = strdup(paths);
			if (paths_copy == NULL) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}
			char* ptoken;
			char* pcopy_ptr = paths_copy;
			while ((ptoken = strsep(&pcopy_ptr, ":")) != NULL) {
				snprintf(full_path, MAX_PATH_LEN, "%s/%s", ptoken, args[0]);
				if (access(full_path, X_OK) == 0) {
					found_path = true;
					break;
				}
			}
			free(paths_copy);
			if (found_path) {
				rc = fork();
				if (rc < 0) { // fork fail
					write(STDERR_FILENO, error_message, strlen(error_message));
					free(full_path);
					exit(1);
				} else if (rc == 0) { // child 
					args[0] = full_path;
					execv(args[0], args);
					write(STDERR_FILENO, error_message, strlen(error_message));
					free(full_path);
					exit(1);
				} else {
					wait(NULL);
					free(full_path);
				}
			} else {
				write(STDERR_FILENO, error_message, strlen(error_message));
				free(full_path);
			}
		}
	}
	return 0;
}

bool is_builtin(char* cmd) {
	if (cmd == NULL || *cmd == '\0') return false;
	for (int i = 0; built_in_cmds[i] != NULL; i++)
		if (strcmp(cmd, built_in_cmds[i]) == 0) return true;
	return false;
}
