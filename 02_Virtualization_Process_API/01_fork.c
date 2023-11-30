/*
Write a program that calls fork(). Before calling fork(), have the main process access a 
variable (e.g., x) and set its value to something (e.g., 100). What value is the variable
in the child process? What happens to the variable when both the child and parent change
the value of x?
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int x = 100;

    int rc = fork();

    if(rc < 0) {
        printf("Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc == 0) {
        //child process
        printf("Child Process: Before x = %d\n",x);
        x = 200;
        printf("Child Process: After x = %d\n",x);
    }
    else {
        //parent process
        printf("Parent Process: Before x = %d\n",x);
        x = 400;
        printf("Parent Process: After x = %d\n",x);
    }
}