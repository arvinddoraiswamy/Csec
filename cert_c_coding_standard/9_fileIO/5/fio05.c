#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    struct stat orig_st;
    struct stat new_st;
    char *file_name;
     
    /*
        Here we open the first file and obtain a handle to it.
    */
    int fd = open("1.txt", O_RDONLY);
    if (fd == -1) {
        printf("%s\n", "Could not open file\n");
    }
     
    /*
        Obtain information about the file and store it in a structure orig_st.
    */
    if (fstat(fd, &orig_st) == -1) {
        printf("%s\n", "Fstat didn't complete successfully\n");
    }
    else {
        printf("Original Inode is %zu\n", orig_st.st_ino);
        printf("Original Device is %zu\n", orig_st.st_dev);
    }

    /*
        Close the file descriptor and invalidate it.
    */
    close(fd);
    fd = -1;
     
    /*
        Sleeping ... for demo purposes
    */
    printf("Now sleeping for a while\n");
    sleep(10);

    /*
        Here we open the old file and obtain a new handle to it.
    */
    fd = open("1.txt", O_RDONLY);
    if (fd == -1) {
        printf("%s\n", "Could not open file\n");
    }
     
    /*
        Obtain information about the file and store it in a new structure new_st.
    */
    if (fstat(fd, &new_st) == -1) {
        printf("%s\n", "Fstat didn't complete successfully\n");
    }
    else{
        printf("Current Inode is %zu\n", new_st.st_ino);
        printf("Current Device is %zu\n", new_st.st_dev);
    }
     
    /*
        - Remove the first file (1.txt).
        
        - Create a soft link with the same name as the first file to another file while the program is sleeping. In real
          life, a different program would do this without anyone's knowledge.

        - Interestingly though, removal of the file and then copying a new file and renaming it..fails. The new file when created with the same
          name grabs the same inode as the old file and passes the check. So I'm er... not sure about the defense :)

        - Compare the information stored in the old and the new structures. These should match - otherwise it means that the file has changed.
    */
    
    if ((orig_st.st_dev != new_st.st_dev) || (orig_st.st_ino != new_st.st_ino)) {
        printf("%s\n", "The file 1.txt has been modified\n");
        exit(0);
    }
       
    /*
        If it's the same file, read from it.This returns a pointer to 20 bytes of memory.
    */ 
    char *buffer;
    int result;
    buffer = malloc(20);

    if (buffer != NULL) {
        result = read(fd, buffer, 100);
        printf("Result is %s\n",buffer);
    }
    else{
        printf("malloc failed\n");
    }

    /*And it'll crash here, if you've pushed in more than what you've allocated*/
    free(buffer);
     
    close(fd);
    fd = -1;
}
