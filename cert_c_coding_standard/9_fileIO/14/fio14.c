#include <stdio.h>

int main(int argc, char *argv[]) {
    char buffer [256];
    /* Initialize file_name */
    FILE *file = fopen("test1", "rb");

    /*
        The file position indicator needs to be set to 1 before you call ungetc() else there is unpredictable behavior.
    */
    //fseek(file, 1, SEEK_SET);
    printf("Current position is %lu\n",ftell(file));

    /*
       If file pointer position is 0, ungetc() generates unpredictable results. The file pointer value is a random number, 
       and ungetc() doesn't replace the pos-1 character at all... just prints the pushed character with the entire stream.

       The point is to never have th file position indicator set to 0 when calling ungetc()
    */

    ungetc('+',file);
    printf("Current position if position is 0 when ungetc is called is %lu\n",ftell(file));
    fgets(buffer, 255, file);
    fputs(buffer, stdout);

    fclose(file);

    file = fopen("test1", "wb");
    fputs(argv[1], file);

    /*
        The docs recommend never to use SEEK_END as it is not portable. But using it with the right offset seems to work okay. Not sure what 
        the problem is :)

        The reason for unpredictability is apparently...because null characters can be part of the stream that's written to the file. But fputs
        anyway ignores all null characters. So this is all unclear :)
    */

    fseek(file,ftell(file),SEEK_SET);
    //fseek(file, 0, SEEK_END);
    printf("\nCurrent position is %lu\n",ftell(file));
    fputs("crap\n", file);
    fclose(file);
}
