#include <stdio.h>
#include <stdlib.h>
 
enum { BUFFER_SIZE = 1024 };
 
void func(FILE *file) {
  char buf[BUFFER_SIZE];
  
  /* Deliberately close file to ensure the fgets() call fails */
  fclose(file);
 
  if (fgets(buf, sizeof(buf), file) == NULL) {
    printf("Content retrieval failed\n");

    /*
        Not flushing this buffer but printing it or using its contents at a later stage can cause funny things to happen.
        Ensure that this buffer is always flushed. Again though, I'm not sure how on
     */
    *buf = '\0';
  }
  else {
    printf("Content retrieved successfully\n");
  }

  /* If this bit doesn't happen, where the printf actually accesses the data, it's ok and you don't need to flush */
  printf("Buffer content is %s\n", buf);
  exit(0);
}

int main(){
    FILE *fp = fopen("test", "r");
    if (fp != NULL){
        func(fp);
    }
    fclose(fp);
}
