#include <stdio.h>
#include <stdlib.h>
 
int verify_file(const char *filename) {
  char *buffer = malloc(100);
  char *canonicalized_filename = malloc(100);

  /* 
    This function canonicalizes all user input. Ensure that this is used, followed by white list validation and then processing of the file.
    In this case, it will strip all the ../ characters or resolve the soft link and reveal the actual path that is used.
  */
  canonicalized_filename = canonicalize_file_name(filename);
  printf("%s\n", canonicalized_filename);

  /*
    Do validation here... before the file is actually opened. Maybe stuff like, the file needs to be opened must exist in a specific directory.
    That would result in a failed attempt to open /etc/passwd.
  */
  FILE *fd = fopen(filename, "r");
  if (fd == NULL) {
    printf("File cannot be opened\n");
  }
  else {
    fread(buffer, 2, 100, fd);
    printf("%s\n",buffer);
  }
  return 0;
}

int main(int argc, char *argv[]){
   /*
    Pass a filename which is a softlink (p1) or a long directory path (../../../../../../../../../../../etc/passwd) as argv[1]
   */
   verify_file(argv[1]);
}
