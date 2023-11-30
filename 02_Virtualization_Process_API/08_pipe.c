/*
Write a program that creates two children, 
and connects the standard output of one to the standard input of the other, 
using the pipe() system call.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child1, child2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process
    if ((child1 = fork()) == -1) {
        perror("Error forking first child");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // First child process

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        // Execute a command (e.g., echo)
        execlp("echo", "echo", "Hello from Child 1", NULL);
    }

    // Create the second child process
    if ((child2 = fork()) == -1) {
        perror("Error forking second child");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {
        // Second child process

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        // Execute a command (e.g., cat)
        execlp("cat", "cat", NULL);
    }

    // Close both ends of the pipe in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}