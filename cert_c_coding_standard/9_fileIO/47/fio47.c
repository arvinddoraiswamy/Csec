#include <stdio.h>
 
void func(void) {
  const char *error_msg = "Resource not available to user.";
  int error_type = 3;

  /* 
     There is a format string mismatch here which causes a seg fault when run. In fairness though, a warning is also thrown by default so I
     doubt this will be ignored at all in the first place. Also remember it is not only printf that is subject to this warning, it's any function
     that uses a format string.
  */
  //printf("Error (type %s): %d\n", error_type, error_msg);

  /*
     Instead interchange the places of these arguments and all will be well.
  */
  printf("Error (type %d): %s\n", error_type, error_msg);
}

int main(){
    func();
}
