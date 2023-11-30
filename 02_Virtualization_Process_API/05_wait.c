/*
Now write a program that uses wait() to wait for the child process to finish in the parent. 
What does wait() return? What happens if you use wait() in the child?

In the parent process, wait(&status) is used to wait for the child process to finish.
 wait() returns the process ID of the terminated child process. 
 The status parameter is used to store information about the child process's termination status.

If the child process exits normally, 
WIFEXITED(status) will evaluate to true,
 and you can retrieve the exit status using WEXITSTATUS(status). 
 If the child process is terminated by a signal, WIFSIGNALED(status) will be true,
  and you can retrieve the terminating signal using WTERMSIG(status).

If you use wait() in the child process, it may lead to undefined behavior.
 The wait() system call is meant to be used by the parent process to wait for 
 its child processes. If a child process tries to wait for its child, it might return 
 an error or unexpected results. It's generally not recommended to use wait() in the child process.
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

        // Wait for the child to finish
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent process: Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent process: Child terminated by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
