#include <stdio.h>
  
void cleanup(void) {
  printf("All cleaned up!\n");

  /* This fflush is just an "in case" something is pending run */
  if (fflush(stdout) == EOF) {
    printf("Could not close stream inside exit handler\n");
  }
}
 
int main(void) {
  atexit(cleanup);
  printf("Doing important stuff\n");
  /* 
    If you use fclose(stdout) here, the stream is closed and the exit handler will not be able to run printf.
    Running fflush() instead forces a write of all pending data to that stream - in this case stdout.
  */
  if (fflush(stdout) == EOF) {
    printf("Could not close stream\n");
  }
  return 0;
}
