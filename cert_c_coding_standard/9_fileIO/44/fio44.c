#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int opener(FILE *file) {
  int rc;
  fpos_t offset;
 
  memset(&offset, 3, sizeof(offset));
 
  if (file == NULL) { 
    return -1;
  }
 
  /* 
    This is a must apparently and the actual start of the file is stored in offset. If this call is not made and you directly call fsetpos
    after the fread, behavior is undefined. 

    If memset of "offset" above is set to 0, as shown above you don't need the fgetpos below here. The code will work without that. But if say,
    for some reason "offset" is set to something that is non-zero - then the code will fail.

    You could try and keep track of where the value of offset is changed, but its far easier to just use fgetpos() each time before you use
    fsetpos() again.
  */

  rc = fgetpos(file, &offset);
  if (rc != 0 ) {
    return rc;
  }

  char *buffer = malloc(10);
  int x = fread(buffer, 1, 10, file);

  if (x == 0){
    printf("Fread failed\n");
    exit(0);
  }
  else{
    printf("Buffer content is: %s\n", buffer);
  }

  rc = fsetpos(file, &offset);
  if (rc != 0 ) {
    printf("Fsetpos fails\n");
    return rc;
  }
  else{
    printf("File position is %d\n", rc);
  }
 
  return 0;
}

int main(){
    FILE *file;
    file = fopen("test1", "r");
    if (file != NULL){
        opener(file);
    }
    else{
        printf("File opening failed\n");
        exit(0);
    }
}
