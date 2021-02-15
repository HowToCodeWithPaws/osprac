#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/// времени на лабы не хватает
/// спасибо за внимание

int main() {
  int child_to_parent[2], parent_to_child[2];
  pid_t forking;
  size_t size;
  char parent_message[23];
  char child_message[23];

  if (pipe(child_to_parent) < 0) {
    printf("Can\'t open child-to-parent pipe\n");
    exit(-1);
  }

  if (pipe(parent_to_child) < 0) {
    printf("Can\'t open parent-to-child pipe\n");
    exit(-1);
  }

  forking = fork();

  if (forking < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (forking > 0) {

    /* Parent process */

    printf("i am parent-process\n");

    size = write(parent_to_child[1], "Hello, difficult child!", 23);

    if (size != 23) {
      printf("parent: Can\'t write all string to pipe\n");
      exit(-1);
    }

    printf("\nparent: Message to child written\n\n");

    if (close(parent_to_child[1]) < 0) {
      printf("parent: Can\'t close writing side of pipe\n");
      exit(-1);
    }

    size = read(child_to_parent[0], child_message, 23);

    if (size < 0) {
      printf("parent: Can\'t read string from pipe\n");
      exit(-1);
    }

    printf("Parent reads, message from child: %s\n\n", child_message);

    if (close(child_to_parent[0]) < 0) {
      printf("parent: Can\'t close reading side of pipe\n");
      exit(-1);
    }

    printf("Parent exits\n");

  } else {

    /* Child process */

    printf("i am child-process\n");

    size = read(parent_to_child[0], parent_message, 23);

    if (size < 0) {
      printf("child: Can\'t read string from pipe\n");
      exit(-1);
    }

    printf("Child reads, message from parent: %s\n\n", parent_message);

    if (close(parent_to_child[0]) < 0) {
      printf("child: Can\'t close reading side of pipe\n");
      exit(-1);
    }

    size = write(child_to_parent[1], "Hello, parental figure!", 23);

    if (size != 23) {
      printf("child: Can\'t write all string to pipe\n");
      exit(-1);
    }

    printf("child: message written\n\n");

    printf("Child exits\n");
  }

  return 0;
}
