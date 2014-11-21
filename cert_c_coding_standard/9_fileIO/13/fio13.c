//http://www.tutorialspoint.com/c_standard_library/c_function_ungetc.htm
//https://www.securecoding.cert.org/confluence/display/seccode/FIO13-C.+Never+push+back+anything+other+than+one+read+character

/*
    It's unclear why this has a security impact although functionally it would be flawed code.
*/

#include <stdio.h>

int main ()
{
   FILE *fp;
   int c;
   char buffer [256];

   fp = fopen("file.txt", "r");
   if( fp == NULL ) 
   {
      perror("Error in opening file");
      return(-1);
   }
   while(!feof(fp)) 
   {
      c = getc (fp);
      /* replace ! with + */
      if( c == '!' ) 
      {
         ungetc ('t', fp);
         ungetc ('+', fp);

         //This causes the file pointer to be reset and the ungetc() operations ignored.
         fseek(fp, 2, SEEK_CUR);
      }
      else 
      {
         ungetc(c, fp);
      }
      fgets(buffer, 255, fp);
      fputs(buffer, stdout);
   }
   return(0);
}
