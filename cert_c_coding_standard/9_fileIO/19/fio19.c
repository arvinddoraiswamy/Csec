//https://www.securecoding.cert.org/confluence/display/seccode/FIO19-C.+Do+not+use+fseek%28%29+and+ftell%28%29+to+compute+the+size+of+a+regular+file
//https://stackoverflow.com/questions/5957845/using-fseek-and-ftell-to-determine-the-size-of-a-file-has-a-vulnerability

/* Seems to work okay though, even with plenty of garbage null characters at the end of the file */
/* Checked by comparing output with the 'wc' binary */

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    long file_size;
    char *buffer;
     
    fp = fopen("foo.txt", "rb");
    if (fp == NULL) {
        printf("Cannot open file\n");
    }
     
    if (fseek(fp, 0 , SEEK_END) != 0) {
        printf("Cannot reposition file pointer\n");
    }
     
    file_size = ftell(fp);
    if (file_size == -1) {
        printf("File size calculation failed\n");
    }
    else {
        printf("File size is %lu\n", file_size);
    }
     
    buffer = (char*)malloc(file_size);
    if (buffer == NULL) {
        printf("Size allocation failed\n");
    }
}
