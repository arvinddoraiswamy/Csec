//https://www.securecoding.cert.org/confluence/display/seccode/FIO38-C.+Do+not+copy+a+FILE+object
//http://www.tutorialspoint.com/cprogramming/c_pointers.htm

#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
  /*
    Here you are copying the VALUE of the file descriptor STDOUT to a new object and using that in the fputs() call. 

    fputs() tries to write to the address stored at the VALUE...which doesn't exist at all and it crashes the program.

    But again, this isn't a "security" threat as such - more bad coding practices and will get caught during development.

  FILE my_stdout = *stdout;
  if (fputs("Hello, World!\n", &my_stdout) == EOF) {
    printf("Fputs failed\n");
    exit(0);
  }
  */

  /*
    But this works because it is not a copy. You set the value of the new pointer to the address of stdout and use it in fputs().
  */
  FILE *my_stdout = stdout;
  if (fputs("Hello, World!\n", my_stdout) == EOF) {
    printf("Fputs failed\n");
    exit(0);
  }
  return 0;
}
