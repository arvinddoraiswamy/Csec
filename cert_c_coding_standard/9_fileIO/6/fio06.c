//https://www.securecoding.cert.org/confluence/display/seccode/FIO06-C.+Create+files+with+appropriate+access+permissions


#include <fcntl.h>
#include <stdio.h>

int main() {
    char *file_name="test1";
    int file_access_permissions;
    file_access_permissions = 0700; //The 0700 is important - it can't be 700.
     
    /*Undefined behavior if permissions are not set on a file as a 3rd argument in the open() call. */
    //int fd = open( file_name, O_CREAT|O_WRONLY);

    int fd = open( file_name, O_CREAT|O_WRONLY, file_access_permissions);

    /*
    If the file is created with 0100 the TRUNC fails, but if it was created with 0700 it succeeds. 'rm' from the shell directly though
    succeeds in both cases. It's unclear why.
    */
    int fd = open( file_name, O_TRUNC);

    if (fd == -1){
        printf("%s\n", "Could not perform file operation");
    }
}
