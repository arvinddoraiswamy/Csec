//https://www.securecoding.cert.org/confluence/display/seccode/FIO30-C.+Exclude+user+input+from+format+strings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
 
//*user comes from argv[1]
void incorrect_password(const char *user) {
  int ret;
  static const char msg_format[] = "%s cannot be authenticated.\n";

  //This is bad because you are accepting input from a user and calculating the length based on that. So the user could really do anything.
  size_t len = strlen(user) + sizeof(msg_format);
  char *msg = (char *)malloc(len);

  if (msg == NULL) {
    printf("Could not allocate memory\n");
    exit(0);
  }

  //Constructed from the user argument which comes from the command line - user defined.
  ret = snprintf(msg, len, msg_format, user);

  if (ret < 0) { 
    printf("Snprintf did not return successfully\n");
  } else if (ret >= len) {
    printf("Snprintf truncated the message\n");
  }

  //This is the call that is vulnerable to a buffer overflow.
  //fprintf(stderr, msg);

  //This fixes it, by using a format string msg_format.
  fprintf(stderr, msg_format, user);

  //Or you use fputs() instead which doesn't 'interpret' the format string at all like fprintf.
  //fputs(msg, stderr);

  syslog(LOG_INFO, msg);
  free(msg);
}

int main(int argc, char *argv[]){
   incorrect_password(argv[1]); 
}
