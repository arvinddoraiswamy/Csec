#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    /*
        If the directory "f1" doesn't have enough permissions access() will return -1 and try to rename the file. Not what you wanted.
    */
    const char *src_file = "f1/test1";
    const char *dest_file = "f1/test2";

    int x= access(dest_file, F_OK);

    /*
        If access fails or returns -1... it means that .. maybe the file doesn't exist. It could also mean though that the program does not
        have enough permissions on the directory/file.

        NOTE: As long as the 'x' bit is set on the directory for (owner, group, others depending on who is running the program) access() will
        succeed. It does NOT matter if the permissions of the actual file are 000 as long as the dir that the file is IN has the relevant 'x'
        bit set - the access() call still succeeds.

        'x' on directory set - access() will detect file presence/absence - it's then up to rename to see if it can work. If the file doesn't
        have write permissions - rename() will fail.
    */
    if (x != 0) {
      printf("The file may not exist OR the program might not have enough permissions on this file\n");
      if (rename(src_file, dest_file) == 0) {
        printf("File was successfully renamed\n");
      }
      else{
        printf("Rename failed. The program might not have enough permissions to perform this operation\n");
      }
    } 
    /*
        If access returns 0 ..it succeeded...which means that the destination file exists. And should not be renamed.
    */
    else {
        printf("File exists. Rename fails.\n");
        exit(0);
    }
}
