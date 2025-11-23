#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

#define MAX_ARGS 10

const char error_message[30] = "An error has occurred\n";
const char* built_in_cmds[] = { "exit", "cd", "path", NULL };

bool is_builtin(char* cmd);

int main(int argc, char** argv) {
	char* input = NULL;
	size_t buffer_size = 0;
	ssize_t nread;
	pid_t rc;
	char* args[MAX_ARGS];
	char *token;
	const char* delimiter =  " ";
	int arg_idx;
	char* inputptr;

	for(;;) {
		printf("wish> ");
		nread = getline(&input, &buffer_size, stdin);

		// ctrl + D: exit
		if (nread == -1) { 
			free(input);
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
			if (strcmp(args[0], "exit") == 0)
				exit(0);
			else if (strcmp(args[0], "cd") == 0) {
				if (arg_idx == 1 || chdir(args[1]) != 0) 
					write(STDERR_FILENO, error_message, strlen(error_message));
			}
		} else if (arg_idx) {
			rc = fork();
			if (rc < 0) { // fork fail
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (rc == 0) { // child 
				execvp(args[0], args);
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			} else {
				wait(NULL);
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
