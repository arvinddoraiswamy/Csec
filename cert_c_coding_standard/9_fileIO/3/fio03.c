//Take the "x" out and it will overwrite an existing file. Its useful in some cases, but more to identify a bug early in the dev cycle.
//Similarly for open take the O_CREAT|O_EXCL argument out. That controls the overwrite of the file.

//https://www.securecoding.cert.org/confluence/display/seccode/FIO03-C.+Do+not+make+assumptions+about+fopen%28%29+and+file+creation

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[1]) {
    FILE *fp;

    /*
        Doing this will cause a file to be overwritten, assuming the user has permissions to do so. Sometimes this might be intended behavior
        in which case, this test can be ignored. 
        - fopen: Adding the 'x' flag, prevents this from happening.
        - open:  Adding the O_CREAT and O_EXCL flags prevents this from happening.
    */
    //fp = fopen("test3", "w");
    
    /*
        This is how it needs to be written. The "test3" file will not be overwritten if it exists and these flags are set.
    */
    fp = fopen("test3", "wx");
    if (fp == NULL){
        printf("Fopen - File already exists. Cannot overwrite it.\n");
    }
    else{
        printf("Fopen - Opening file in write mode.\n");
    }

    int fd;
    //fd = open("test34", O_WRONLY);
    /*
        This is how it needs to be written. The "test34" file will not be overwritten if it exists and these flags are set.
    */
    fd = open("test34", O_CREAT|O_WRONLY|O_EXCL);
    if (fd == -1){
        printf("Open - File already exists. Cannot overwrite it.\n");
    }
    else{
        printf("Open - Opening file in write mode\n");
    }
}
