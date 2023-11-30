/*
Write a slight modification of the previous program,
this time using waitpid() instead of wait(). 
When would waitpid() be useful?

The waitpid() function is useful when you want to wait for a specific child process
 rather than any child process, as is the case with wait(). 
 You can specify the process ID of the child you want to wait for as an argument to waitpid().

 pid_t waitpid(pid_t pid, int *status, int options);

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

        printf("Child process\n");
        sleep(2); // Simulating some work in the child

        printf("Child process done\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;

        // Wait for the child to finish using waitpid()
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Parent process: Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent process: Child terminated by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}