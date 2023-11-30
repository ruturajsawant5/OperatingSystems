/*
Write a program that creates a child process, 
and then in the child closes standard output (STDOUT_FILENO). 
What happens if the child calls printf() to print some output after closing the descriptor?

When the child process closes the standard output (STDOUT_FILENO) using the close() system call, 
any subsequent attempt to use printf() or 
any other function that writes to standard output will result in undefined behavior.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(STDOUT_FILENO); // Close standard output

        // Attempt to print using printf after closing STDOUT_FILENO
        printf("This will not be printed\n");
    } else {
        // Parent process
        wait(NULL); // Wait for the child to finish
    }

    return 0;
}