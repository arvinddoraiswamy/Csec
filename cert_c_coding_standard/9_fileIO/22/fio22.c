#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
 
int main() {
  char *cmd;
  //int fd = open("test.txt", O_RDONLY | O_CLOEXEC);
  int fd = open("test.txt", O_RDONLY);
  if (fd == -1) {
    printf("Could not open file\n");
  }
  else {
  }
 
  cmd = "/bin/bash";
  if (system(cmd) == -1) {
    printf("Could not run command\n");
  }
  else {
    int child_pid = fork();
    printf("Child process ID is %d\n", child_pid);

    /*  At this point, since the file descriptor that was used to open test.txt is not closed, it can be accessed by the child process that is
        forked. This is normal behavior, but becomes a problem if the resource opened by the parent process was private and NOT supposed to be
        accessed by the child process.

        The best idea is to close the file descriptor as soon as its work is done. If that isn't possible, ensure that you open the file
        with the O_CLOEXEC flag. This prevents a file descriptor from being accessible by 2 programs simultaenously. So the child can't do
        anything if the file descriptor is open.
    */
  }
}
