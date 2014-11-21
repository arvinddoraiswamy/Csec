//https://www.securecoding.cert.org/confluence/display/seccode/FIO21-C.+Do+not+create+temporary+files+in+shared+directories

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
extern int secure_dir(const char *sdn);
 
int main() {
  const char *sdn = "/securedir";
  char sfn[] = "/securedir/temp-XXXXXX";
  FILE *sfp;
 
  /* Ensure that /securedir is protected using strong permissions */
 
  /* Do not use tmpfile or tmpnam. They are not secure.
     tmpname does not generate an unpredictable name.
     tmpfile does not allow you to choose the directory in which temporary files are created.
  */
  int fd = mkstemp(sfn);
  if (fd == -1) {
    printf("Could not create temporary file\n");
  }
 
  /* mkstemp returns a file descriptor so we use fdopen instead of fopen */
  /* File created has permissions of 600 */
  sfp = fdopen(fd, "w+");
  if (sfp == NULL) {
    close(fd);
    printf("Could not open temp file to write\n");
  }
 
  fwrite("Hello world",10,1,sfp);
  fclose(sfp); /* Also closes fd */

  /* Ensure that you delete the temp file at the end */
  unlink(sfn);
}
