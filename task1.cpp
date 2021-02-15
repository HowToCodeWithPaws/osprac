#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;

  printf("we are going to read and print from myfile.txt\n\n");

  if ((fd = open("myfile.txt", O_RDONLY)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  ssize_t amount_read;
  char readings;

  while (1) {
    amount_read = read(fd, &readings, 1);

    if (amount_read == 0) {
      break;
    }

    if (amount_read < 0) {
      printf("Can\'t read file\n");
      exit(-8);
    }

    ssize_t written = write(1, &readings, 1);

    if (written != amount_read) {
      printf("Can\'t write to console\n");
      exit(-12);
    }
  }

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }

  printf("\n\nwe finished reading and printing from myfile.txt\n");

  return 0;
}
