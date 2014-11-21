//https://www.securecoding.cert.org/confluence/display/seccode/FIO14-C.+Understand+the+difference+between+text+mode+and+binary+mode+with+file+streams

//Unclear what security impact this has..again.

#include <stdio.h>

int main() {
    char buffer [256];
    /* Initialize file_name */
    FILE *file = fopen("test1", "rb");

    rewind(file);
    printf("Current position is %lu\n",ftell(file));

    /* Apparently if file pointer position is 0, ungetc() generates unpredictable results. Except that it still worked :D */

    ungetc('+',file);
    fgets(buffer, 255, file);
    fputs(buffer, stdout);

    fclose(file);

    file = fopen("test1", "wb");
    fputs("ABCDEFGH\n", file);

    /* The mode has to be SEEK_SET , else it doesn't work. The position too works out to 16 for some reason with SEEK_END, it should be 8.
       All good with SEEK_SET though.
    */

    fseek(file,ftell(file),SEEK_SET);
    printf("\nCurrent position is %lu\n",ftell(file));
    fputs("crap\n", file);
    fclose(file);
}
