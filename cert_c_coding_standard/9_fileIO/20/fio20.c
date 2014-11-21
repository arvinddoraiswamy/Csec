/*
    https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=3226
    
    This simply says, when you're passing user input to a program, if you want to make sure that all your user input is accepted exactly as
    is, the second last character should be a newline or EOF. The last character is a null byte that fgets automatically adds.

    If this is important to you, add code to your program that checks if the user's second last character IS a newline and terminate the code
    if it is not.

    It doesn't handle cases where input is clearly smaller than the buffer size as that is not the subject of discussion here.
*/

#include <stdio.h>
#include <string.h>

int main() {
    char buf[8];
    buf[0]='a';
    buf[1]='a';
    buf[2]='a';
    buf[3]='a';
    buf[4]='a';
    buf[5]='a';
    buf[6]='a';
    buf[7]='a';

    size_t len = strlen(buf);
    if (fgets(buf, sizeof(buf), stdin)) {
        if (len != 0 && buf[len-1] == '\n') {
            printf("The non truncated user input %s\n", buf);
        }
        else {
            printf("Second last character is %d or %c\n",buf[len-1],buf[len-1]);
            printf("The truncated user input %s\n", buf);
        }
    }
    else {
        printf("Error getting data from the user\n");
    }
}
