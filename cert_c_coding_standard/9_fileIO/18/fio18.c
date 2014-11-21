#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main() {
    char *buffer = NULL;
    size_t size1;
    FILE *filedes;
     
    filedes = fopen("out.txt", "w+");
    if (filedes == NULL){
        printf("Could not open file\n");
    }
 
    /* A total of 6 characters including the null byte can be copied into buffer */    
    size1 = 6;
    buffer = (char *)calloc( 1, size1);
    if (buffer == NULL) {
        printf("Could not allocate memory\n");
    }

    /* Copies the first 6 characters of the alphabet string into the buffer. Note that there is no null byte here. */
    strncpy(buffer, "abcdef", 6);

    /* Add a null byte like this as the last character */
    //strncpy(buffer, "abcde\0", 6);

    fwrite(buffer, 1, 6, filedes);

    /* Write a few more characters in for demo purposes. The file will now contain abcdefpassword - a total of 14 characters */
    fwrite("password", 1, 8, filedes);

    free(buffer);
    buffer = NULL;
    fclose(filedes);

    /* The problem now starts when another part of the program assumes that the string was null-byte terminated and tries to read 7 chars
       In reality a null byte was never written and hence the 7th character is leaked instead.
    */

    filedes = fopen("out.txt", "r");
    if (filedes == NULL){
        printf("Could not open file\n");
    }
    buffer = (char *)calloc( 1, 10);
    if (buffer == NULL) {
        printf("Could not allocate memory\n");
    }

    /*
        Note that the code tries to read back 7 characters, assuming that there is a null byte too that has been written to the file.
        But since there 
    */
    fread(buffer, 1, 7, filedes);
    printf("Buffer read from file is %s\n", buffer);
}
