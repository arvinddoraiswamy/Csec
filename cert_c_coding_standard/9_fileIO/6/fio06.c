#include <fcntl.h>
#include <stdio.h>

int main() {
    char *file_name="test1";
    int file_access_permissions;
     
    /*
        Undefined behavior if permissions are not set on a file as a 3rd argument in the open() call. Files with random permissions get created.
    */
    int fd = open( file_name, O_CREAT|O_WRONLY);

    /*
        This is the correct way to use the open() call - with the 3rd permission argument. 
        
        Interestingly though, if the file is created with 0100 the TRUNC fails, but if it was created with 0700 it succeeds. 'rm' from the shell 
        directly though succeeds in both cases.  It's unclear why - even though I don't have any permissions in the first case.
    */

    /*
    file_access_permissions = 0700; 
    int fd = open( file_name, O_CREAT|O_WRONLY, file_access_permissions);
    */
    fd = open( file_name, O_TRUNC);
    if (fd == -1){
        printf("%s\n", "Could not perform file operation");
    }
}
