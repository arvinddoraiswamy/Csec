/*https://www.securecoding.cert.org/confluence/display/seccode/FIO01-C.+Be+careful+using+functions+that+use+file+names+for+identification*/
/*http://cwe.mitre.org/data/definitions/367.html*/

//Start the program. It'll open 1.txt. While it sleeps, rename 2.txt to 1.txt, so the contents of 2.txt get read instead.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    char *file_name;
    FILE *f_ptr;
    char *buffer;
    size_t result;
 
    /* Initialize file_name */
    f_ptr = fopen("1.txt", "r");
    if (f_ptr == NULL) {
        printf("File not found\n");
    }

    /* This returns a pointer to 20 bytes of memory.*/ 
    buffer = malloc(20);

    /*... Sleeping ... for demo purposes*/
    printf("Now sleeping for a while\n");
    sleep(2);

    /* But...which file is it reading from? */
    if (buffer != NULL) {
        result = fread(buffer,1,10,f_ptr);
        printf("Result is %s\n",buffer);
    }
    else{
        printf("malloc failed\n");
    }

    /*And it'll crash here, if you've pushed in more than what you've allocated*/
    free(buffer);
    
    if (fclose(f_ptr) != 0) {
        exit(1);
    }
}
