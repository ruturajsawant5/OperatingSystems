/*
Write a program that opens a file (with the open() system call) and
then calls fork() to create a new process. 
Can both the child and parent access the file descriptor returned by open()? 
ans = child inherits parent open file descriptors
What happens when they are writing to the file concurrently, i.e., at the same time?
ans = order of data
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main() {
    int fd;
    int rc;
    int i;

    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd < 0) {
        printf("open failed\n");
        exit(EXIT_FAILURE);
    }

    rc = fork();

    if(rc < 0) {
        printf("Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    else if(rc == 0) {
        //child process
        for(i = 0; i < 10; i++)
            write(fd, "CHILD\n", 6);
        close(fd);
    }
    else {
        //parent process
        for(i = 0; i < 10; i++)
            write(fd, "PARENT\n", 7);
        close(fd);
    }
}