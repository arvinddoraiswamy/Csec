#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    long file_size;
    char *buffer;
    int i=0;
     
    fp = fopen("foo.txt", "rb");
    if (fp == NULL) {
        printf("Cannot open file\n");
    }
     
    /*
        Using this method to calculate file size is apparently not recommended. But it works on all POSIX supporting systems, apparently.
        So TL;DR - There's no vulnerability here :)
    */
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
    else{
        i=0;
        int count= 0;
        while (i < file_size-1) {
            buffer[i] = 'a';
            printf("%d\t%c\n", count, buffer[i]);
            count+=1;
            i+=1;
        }
        buffer[file_size-1]='\0';
        printf("Length of buffer is %lu\n", strlen(buffer));
        printf("Buffer is %s\n", buffer);
    }
}
