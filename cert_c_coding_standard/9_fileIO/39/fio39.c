//https://www.securecoding.cert.org/confluence/display/seccode/FIO39-C.+Do+not+alternately+input+and+output+from+a+stream+without+an+intervening+flush+or+positioning+call

/*
    Note to self: fread() and fwrite() behaved funnily when data length > buffer size was forcibly written.
*/

#include <stdio.h>
#include <stdlib.h>
 
enum { BUFFERSIZE = 8 };
extern void initialize_data(char *data, size_t size);
 
void func(const char *file_name) {
  char data[BUFFERSIZE];
  FILE *file;
 
  file = fopen(file_name, "a+");
  if (file == NULL) {
    printf("Could not open file to append\n");
    exit(0);
  }
 
  if (fwrite("abcdefgh", 1, 8, file) == 0) {
    printf("Could not write to file\n");
    exit(0);
  }
  
  /*
  Not having this bit of code here, repositioning the file pointer will cause undefined behavior. So between READ and WRITE operations
  always have this bit of code.
  */

  /*
  if (fseek(file, 0L, SEEK_SET) != 0) {
    printf("Could not reposition file pointer\n");
    exit(0);
  }
  */
 
  if (fread(data, 1, 8, file) == 0) {
    printf("Could not read content from file\n");
    exit(0);
  }
  else{
    printf("Data is %s\n",data);
  }
 
  if (fclose(file) == EOF) {
    printf("Could not close file\n");
    exit(0);
  }
}

int main(){
    func("test");
    return(0);
}
