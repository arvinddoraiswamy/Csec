#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main (void) {
 
    FILE *fp;
    size_t size;
    long length;
    char *buffer;

    fp = fopen("file.txt", "rb");
 
    if (fp == NULL) {
        printf("Cannot open file\n");
    }
 
    /* Obtain file size */
    if (fseek(fp, 0, SEEK_END) != 0) {
        printf("Could not obtain file size\n");
    }
 
    length = ftell(fp);
 
    if (fseek(fp, 0L, SEEK_SET) != 0) {
        printf("Could not reposition\n");
    }
 
    /* Allocate memory to contain whole file */
    buffer = (char*) malloc(length);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
    }

    /* 
       Reading just 6 characters. The point we're trying to demonstrate here is that if string length that is copied is smaller than the file
       it won't be null terminated and we'll have to terminate it ourselves. Also IF the file itself isn't null-terminated, that too is a
       problem as fread() will just read ...not add a null char if it doesn't see one.
      
       Here we set some following characters to known values. So now when the buffer is printed, you can clearly see that there isn't any
       null termination. So in real life, maybe there's sensitive content in the 7th and 8th character and all that gets echoed to screen.
    */

    buffer[6]='P';
    //buffer[6]='\0';
    buffer[7]='a';
    buffer[8]='s';
    buffer[9]='s';
    buffer[10]='w';

    size=6;
 
    if (fread(buffer, 1, size, fp) < size) {
        printf("Reading from file failed\n");
        exit(0);
    }
    fclose(fp);
 
    /*
        Add a null byte yourself, else it'll print everything till it sees one.
    */
    buffer[5] = '\0';
    printf("Buffer is - %s\n",buffer);

    return 0;
}
