#include <stdio.h>
#include <stdlib.h>

int main ()
{
   FILE *fp;
   fpos_t pos;
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
      printf("\nNext character is %c\n", c);
      /* 
        replace ! with + 
      */
      if( c == '!' ) 
      {
         /*
             This edits the stream, making it available for future read and write operations 
         */
         ungetc ('t', fp);

         /*
            Get the current position and store it in pos.
         */
         if (fgetpos(fp, &pos) == -1) {
            printf("The current file position could not be got\n");
            exit(0);
         }

         /*
            This moves the stream forward by 4 characters and the fputs prints the buffer out.
         */
         fgets(buffer, 5, fp);
         fputs(buffer, stdout);
         fputs("\n", stdout);

         /*
            Remember that saved position? That's restored now, so we're back at the start of the stream.
            If we don't do this fgetpos/fsetpos thing... the ungetc won't work as expected.
            Comment out both the fgetpos and the fsetpos and see what happens.
         */
         if (fsetpos(fp, &pos) == -1) {
            printf("The current file position could not be set\n");
            exit(0);
         }

         /*
            This moves the stream forward by 8 characters and the fputs prints the buffer out.

            At this point, in this example, all that's left after this has been read is the last ! mark. So the loop repeats, with just that
            character pending in the stream. It's not a char by char iteration as one might intuitively expect.
         */
         ungetc ('+', fp);
         fgets(buffer, 9, fp);
         fputs(buffer, stdout);
         fputs("\n", stdout);

         fputs("Iteration done\n", stdout);
      }
      else 
      {
         ungetc(c, fp);
      }
   }
   return(0);
}
