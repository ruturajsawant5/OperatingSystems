/*
Write another program using fork(). 
The child process should print “hello”; 
the parent process should print “goodbye”.
 You should try to ensure that the child process always prints first; 
 can you do this without calling wait() in the parent?
*/
//NOT POSSIBLE


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    printf("hello\n");
  } else {
    while (1) {}
    printf("goodbye\n");
  }

  return 0;
}