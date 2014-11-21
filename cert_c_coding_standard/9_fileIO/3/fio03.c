//Run the script with the "wx" arguments. This will NOT overwrite a file that already exists.
//Take the "x" out and it will overwrite an existing file. Its useful in some cases, but more to identify a bug early in the dev cycle.
//Similarly for open take the O_CREAT|O_EXCL argument out. That controls the overwrite of the file.

//https://www.securecoding.cert.org/confluence/display/seccode/FIO03-C.+Do+not+make+assumptions+about+fopen%28%29+and+file+creation

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[1]) {
    FILE *fp;

    //Using fopen
    fp = fopen("test3", "wx");
    //fp = fopen("test3", "w");
    if (fp == NULL){
        printf("%s\n","Fopen - File already exists. Cannot overwrite it.\n");
    }

    //Using open
    int fd;
    //fd = open("test34", O_CREAT|O_WRONLY|O_EXCL);
    fd = open("test34", O_WRONLY);
    if (fd == -1){
        printf("%s\n","Open - File already exists. Cannot overwrite it.\n");
    }
    else{
        printf("%s\n","Opening file in write mode\n");
    }
}
