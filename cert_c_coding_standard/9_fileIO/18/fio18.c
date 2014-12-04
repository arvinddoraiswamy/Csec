#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main() {
    char *buffer = NULL;
    size_t size1;
    size_t size2;
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

    /* Copies 8 characters of the alphabet string into the buffer. Note that byte 5 is a null byte here. */
    buffer[0]= 'a';
    buffer[1]= 'b';
    buffer[2]= 'c';
    buffer[3]= 'd';
    buffer[4]= '\0';
    buffer[5]= 'f';
    buffer[6]= 'g';
    buffer[7]= 'p';

    /* Despite the null byte being there at byte 5, fwrite ignores it and just copies 8 bytes into buffer and hence out.txt.
       Verify this using wc -c out.txt or hexdump -C out.txt
    */
    size2= 8;

    /*
        Always set the amount to write based on the size of the buffer you are writing
    */
    //size2= strlen(buffer)+1;
    
    fwrite(buffer, 1, size2, filedes);

    free(buffer);
    buffer = NULL;
    fclose(filedes);

    /*
        This could be a problem IF there is some program which reads the file and uses all of the information inside to do something with it
        but ignores the null character.
    */
}
