#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
  /* array with I/O descriptors */
  int pipedes[2];
  /* process id */
  pid_t pid;
  /* now pipedes[0] stores input and
   * pipedes[1] output */
  pipe(pipedes);
  pid = fork();
  /* parant way */
  if (pid > 0) {
    /* message for child */
    char *str = "Greetings my child!\n";
    /* close input from parent side of pipe */
    close(pipedes[0]);
    /* write to pipe output */
    write(pipedes[1], (void *) str, strlen(str) + 1);
    /* close output */
    close(pipedes[1]);
  }
  /* child's way */
  else {
    char buf[1024];
    int len;
    /* close output from child side of pipe */
    close(pipedes[1]);
    /* read while there's something to read in the pipe
     * and write it to the screen */
    while ((len = read(pipedes[0], buf, 1024)) != 0)
      write(2, buf, len);
    close(pipedes[0]);
  }
  return EXIT_SUCCESS;
}
