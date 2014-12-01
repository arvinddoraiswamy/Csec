/*https://www.securecoding.cert.org/confluence/display/seccode/FIO01-C.+Be+careful+using+functions+that+use+file+names+for+identification*/
/*http://cwe.mitre.org/data/definitions/367.html*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    char *file_name;
    FILE *f_ptr;
    char *buffer;
    size_t result;
 
    /* 
    Initialize file_name - this is the filename that we think we're reading. The file handle that is opened is for 1.txt.
    */
    f_ptr = fopen("1.txt", "r");
    if (f_ptr == NULL) {
        printf("File not found\n");
    }

    /*
        Start the program. It'll open 1.txt.  While it sleeps, copy 3.txt to 1.txt instead. This results in the contents of 3.txt being written
        to screen and not that of 1.txt.

        In real life though, its some OTHER program that does the copying of this file, while the original program sleeps.
    */
    printf("Now sleeping for a while\n");
    sleep(5);

    /*
        This returns a pointer to 20 bytes of memory.
    */ 
    buffer = malloc(20);

    /*
        At this point though, the file is it reading from is 3.txt - NOT 1.txt to which the file handle is opened.
    */
    if (buffer != NULL) {
        result = fread(buffer,1,22,f_ptr);
        printf("Result is: %s\n",buffer);
    }
    else{
        printf("malloc failed\n");
    }

    /*
        And it'll crash here, if you've pushed in more than what you've allocated. Although that's not really the point of this POC.
    */
    free(buffer);
    
    if (fclose(f_ptr) != 0) {
        exit(1);
    }
}
