//https://www.securecoding.cert.org/confluence/display/seccode/FIO31-C.+Do+not+open+a+file+that+is+already+open

#include <stdio.h>
 
void do_stuff(void) {
  /* Apparently opening a file, while it is already open can cause a problem. On Linux it does not seem to be a problem at all.
     So I'm not sure what exactly will happen.
  */
  FILE *logfile = fopen("log", "a");
  if (logfile == NULL) {
    printf("Could not open file\n");
  }
 
  /* Write logs pertaining to do_stuff() */
  fprintf(logfile, "do_stuff\n");
}
 
int main(void) {
  FILE *logfile = fopen("log", "a");
  if (logfile == NULL) {
    printf("Could not open file\n");
  }
 
  /* Write logs pertaining to main() */
  fprintf(logfile, "main\n");
 
  do_stuff();
 
  if (fclose(logfile) == EOF) {
    printf("Could not close file\n");
  }
  return 0;
}
