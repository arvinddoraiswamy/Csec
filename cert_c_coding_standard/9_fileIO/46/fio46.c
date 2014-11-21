#include <stdio.h>
 
int close_stdout(void) {
  if (fclose(stdout) == EOF) {
    return -1;
  }
 
  /* The stdout file handle is already closed. So operations should not be performed on it unless STDOUT is redirected to a file. On Linux this
     just fails silently. Behavior though, apparently is undefined - so its best to avoid such code.
  */

  //printf("stdout successfully closed.\n");

  /* Instead use a function like fputs that allows you to specify a stream where the output can be redirected. Printf does not do this. */
  fputs("stdout successfully closed.\n", stderr);

  return 0;
}

int main(){
    close_stdout();
}
