//https://www.securecoding.cert.org/confluence/display/seccode/FIO10-C.+Take+care+when+using+the+rename%28%29+function

#include <stdio.h>
#include <unistd.h>

int main(){
    //If the directory "f1" doesn't have enough permissions access() will return -1 and try to rename the file. Not what you wanted.
    const char *src_file = "f1/test1";
    const char *dest_file = "f1/test2";
     
    if (access(dest_file, F_OK) != 0) {
      /*
        The program must have permissions to make this function call. Otherwise, the file might exist but the access() call still returns -1 which        is not what you expect here. Ensure FIO15 is followed as well - to ensure access() works like you expect it to.
      */

      if (rename(src_file, dest_file) == 0) {
        /* The destination file is removed first and the source file then renamed on Linux. */
        printf("File was successfully renamed\n");
      }
      else{
        printf("Rename failed\n");
      }
    } 
    else {
        printf("File exists. Rename fails.\n");
    }
}
