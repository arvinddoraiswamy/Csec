#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
  
int func(const char *filename) {
  int fd = open(filename, O_RDONLY, S_IRUSR);
  if (-1 == fd) {
    return -1;
  }
  
  char *buf=malloc(10);
  int x = read(fd, buf, 10);
  if (x == -1){
    printf("The read call was unsuccessful\n");
  }
  else{
    printf("Read %d bytes successfully\n",x);
  }

  /*
    Not closing the file descriptor here could potentially lead to resource exhaustion. Although in Linux, someone seems to clean the handle
    up, even if I don't explicitly do so.
  */
  /*if (-1 == close(fd)) {
    return -1;
  }*/
  return 0;
}

int main(){
    func("test1");
}
