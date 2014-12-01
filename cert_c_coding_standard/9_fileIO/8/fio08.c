#include <stdio.h>

int main() {
    char *file_name;
    FILE *file;
    FILE *file_ptr;
     
    file = fopen("test1", "w+");
    if (file == NULL) {
        printf("%s\n","Could not access file\n");
    }
    
    /* 
    In certain implementations (apparently Windows) remove() doesn't remove the file as the file descriptor isn't yet closed. In Ubuntu remove() 
    internally calls unlink() which is the correct behavior - so really both the methods are correct.
    */

    if (remove("test1") != 0) {
        printf("%s\n","Could not remove file\n");
    }

    /*
    if (unlink("test1") != 0) {
        printf("%s\n","Could not remove file\n");
    }
    */

    file_ptr = fopen("test1", "r");
    if (file_ptr == NULL) {
        printf("File not found\n");
    }
     
    fclose(file);
}
