/*
http://www.linux-mag.com/id/700/
https://unix.stackexchange.com/questions/69057/what-are-the-advantages-of-using-named-pipe-over-unnamed-pipe
https://www.securecoding.cert.org/confluence/display/seccode/FIO32-C.+Do+not+perform+operations+on+devices+that+are+only+appropriate+for+files
https://en.wikipedia.org/wiki/Named_pipe#In_Unix
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
 
void func(const char *file_name) {
  /*
  FILE *file;
  if ((file = fopen(file_name, "wb")) == NULL) {
    printf("Cannot open named pipe for writing\n");
  }
  */

  int fd;
  char *buf;


  /*
    This causes the socket to hang. This might be wanted behavior at times, you might deliberately wait for a process to write.
    fd = open(file_name, O_RDONLY);
    fd = open(file_name, O_WRONLY);
  */

  /*
    This does not and just exits. 
    RDONLY - If you don't want to wait for the writing process at all, this is good - use the NONBLOCK flag.
    WRONLY - If you don't want to wait for the reading process at all, use the NONBLOCK flag but also exit...coz the write still hangs. OR some
             error handling, if you don't want to exit.
  */
  //fd = open(file_name, O_NONBLOCK | O_RDONLY);
  fd = open(file_name, O_NONBLOCK | O_WRONLY);

  if (fd == -1) {
    printf("Could not open named pipe for writing\n");
    exit(0);
  }
 
  /*
    This is equivalent to using an unnamed pipe ( | ). Running this passes the "ls" to the FIFO file... and waits... for the 2nd process to
    interact with the FIFO file. In this case we'll just use "cat" which reads from STDIN.

    You'll notice here that .. for named pipes .. the 2nd process can start later, unlike with unnamed pipes ( "|" ).  

    Also... don't use "system" - it's used here just for demo purposes.
  */

  /*
    Try to read

    if (read(fd, buf, 10) == -1) {
        printf("Read failed\n");
        exit(0);
    }
    else{
        printf("Buffer content is: %s\n", buf);
    }
  */

    system("ls -la > fifo_in_same_dir"); 
}

int main(){
  func("fifo_in_same_dir");
}
