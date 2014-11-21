//https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=3473587

/*
  The only modes that the mode must start with are r,w,wx,a,rb,wb,wbx,ab,r+,w+,w+x,a+,rb+,wb+,wb+x,ab+. If it starts with anything else, it
  segfaults. It's unclear though what the security impact of this is going to be - surely the dev is going to fix this before deployment?
*/

#include <stdio.h>

int main(){
    FILE *fp;
    fp = fopen("test1","w");
    if (fp == NULL) {
        printf("File opening failed\n");
    }
    else {
        printf("File opening succeeded\n");
    }
    fclose(fp);
}
