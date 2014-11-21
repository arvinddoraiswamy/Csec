/*https://www.securecoding.cert.org/confluence/display/seccode/FIO05-C.+Identify+files+using+multiple+file+attributes
  Start the program. It'll open 1.txt. While it sleeps, rename 2.txt to 1.txt, so the contents of 2.txt get read instead.
  
  Very similar to fio01 except that the protection mechanisms are better.

  UPDATE: The Inode of a file does not change even after file removal. So the solution fails and it's unclear how to fix it.
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    struct stat orig_st;
    struct stat new_st;
    char *file_name;
     
    int fd = open("1.txt", O_RDONLY);
    if (fd == -1) {
        printf("%s\n", "Could not open file\n");
    }
     
    if (fstat(fd, &orig_st) == -1) {
        printf("%s\n", "Fstat didn't complete successfully\n");
    }
    else {
        printf("Original Inode is %zu\n", orig_st.st_ino);
        printf("Original Device is %zu\n", orig_st.st_dev);
    }

    close(fd);
    fd = -1;
     
    /*... Sleeping ... for demo purposes*/
    printf("Now sleeping for a while\n");
    sleep(10);

    fd = open("1.txt", O_RDONLY);
    if (fd == -1) {
        printf("%s\n", "Could not open file\n");
    }
     
    if (fstat(fd, &new_st) == -1) {
        printf("%s\n", "Fstat didn't complete successfully\n");
    }
    else{
        printf("Current Inode is %zu\n", new_st.st_ino);
        printf("Current Device is %zu\n", new_st.st_dev);
    }
     
    if ((orig_st.st_dev != new_st.st_dev) || (orig_st.st_ino != new_st.st_ino)) {
        printf("%s\n", "The file 1.txt has been modified\n");
        exit(0);
    }
     
    /* If it's the same file, read from it.This returns a pointer to 20 bytes of memory.*/ 
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
