/*
Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls.
 See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), 
 execlp(), execv(), execvp(), and execvpe(). 
 Why do you think there are so many variants of the same basic call?
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process

        // execl() variant
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // execle() variant
        // char *envp[] = {"PATH=/bin", NULL};
        // execle("/bin/ls", "ls", "-l", (char *)NULL, envp);

        // execlp() variant
        // execlp("ls", "ls", "-l", (char *)NULL);

        // execv() variant
        // char *args[] = {"/bin/ls", "ls", "-l", (char *)NULL};
        // execv("/bin/ls", args);

        // execvp() variant
        // char *args[] = {"ls", "-l", (char *)NULL};
        // execvp("ls", args);

        // execvpe() variant
        // char *args[] = {"ls", "-l", (char *)NULL};
        // char *envp[] = {"PATH=/bin", NULL};
        // execvpe("ls", args, envp);

    } else {
        // Parent process
        wait(NULL); // Wait for the child to finish
    }

    return 0;
}