/*
    https://www.securecoding.cert.org/confluence/display/seccode/FIO37-C.+Do+not+assume+that+fgets%28%29+or+fgetws%28%29+returns+a+nonempty+string+when+successful
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
enum { BUFFER_SIZE = 1024 };
 
void func(void) {
  char buf[BUFFER_SIZE];
 
  if (fgets(buf, sizeof(buf), stdin) == NULL) {
    printf("Invalid input received, enter something\n");
    exit(0);
  }
  else {
    /*
        The aim of the code is to remove the newline and get exactly what was entered by the user. Also JUST because fgets() didn't return
        NULL - it doesn't mean that it contains a string. It is just NON NULL - it could contain a NULL byte (\x00).

        This however is bad coz it's possible that the first character of the string is \x00 ... 
        length will become zero....and some random character far far away will get overwritten. I'm not sure if this could introduce a 
        vulnerability but hey.. it's not good code at the least :D.
    */
    buf[strlen(buf) - 1] = '\0';
    printf("String length is %lu\n", strlen(buf));
    printf("Buffer is %s\n", buf);
  }
}

void func1(void) {
  char buf[BUFFER_SIZE];
  char *p;
 
    /*
        This is a better way to replace the newline if one is present. It just searched for the first occurence of newline in the string
        and replaces it with a null character, thus terminating stuff right away.

        And you can still find the exact length of the input, irrespective of where it came from.
    */
  if (fgets(buf, sizeof(buf), stdin)) {
    p = strchr(buf, '\n');
    if (p) {
      printf("Newline character was found. Replacing it with null character.\n");
      *p = '\0';
    }
    printf("String length is %lu\n", strlen(buf));
    printf("Buffer is %s\n", buf);
  }
  else {
    printf("Invalid input received, enter something\n");
    exit(0);
  }
}

int main(){
    //func();
    func1();
}
