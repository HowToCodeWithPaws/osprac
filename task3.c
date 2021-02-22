#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  printf("we are going to try and understand how big the pipe is \nby "
         "feeding it large buffers for writing and reading until it stops "
         "working\n\n");

  int for_pipe[2];
  int size_written, size_attempted_write, size_attempted_read, size_read;
  //начнем с этого значения потому что... ну хотя бы тысячу он точно должен
  //уметь
  size_written = size_attempted_write = size_attempted_read = size_read = 500;
  pid_t forking;

  if (pipe(for_pipe) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  forking = fork();

  if (forking < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (forking == 0) {
    /*ребенок будет писать в фифо, чтобы можно было
     * его убить из родителя после остановки чтения*/
    do {
      size_attempted_write *= 2;
      char *buff = malloc(size_attempted_write);
      size_written = write(for_pipe[1], buff, size_attempted_write);

      printf("tried to write the size %d and wrote %d\n",
             size_attempted_write, size_written);

      free(buff);

      if (size_written != size_attempted_write) {
        break;
      }
    } while (size_written == size_attempted_write);

    printf("\nthe size of pipe as we assume from writing error is %d\n",
           size_written);
  } else {
    /*родитель будет читать, выйдет из цикла и убьет ребенка,
     * когда чтение достигнет своего предела*/
    do {
      size_attempted_read *= 2;
      char *buff = malloc(size_attempted_read);
      size_read = read(for_pipe[0], buff, size_attempted_read);

      printf("tried to read the size %d and read %d\n",
             size_attempted_read, size_read);

      free(buff);

      if (size_read != size_attempted_read) {
        break;
      }
    } while (size_read == size_attempted_read);

    printf("\nthe size of pipe as we assume from reading error is %d\n",
           size_read);

    kill(forking, SIGINT);
  }

  printf("\nthe end\n");
  return 0;
}
