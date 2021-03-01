#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char message_array[4096];
  char *message = message_array;
  char *memory;
  int shmid;
  char pathname[] = "oscourse/05-4.c";
  key_t key;
  int file;
  ssize_t amount_read;
  char symbol;
  int iteration = 0;

  printf("firstly we are going to read from task1_writer.c\n");

  if ((file = open("task1_writer.c", O_RDONLY)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  while (1) {
    amount_read = read(file, &symbol, 1);

    if (amount_read == 0) {
      break;
    }

    if (amount_read < 0) {
      printf("Can\'t read file\n");
      exit(-8);
    }

    message_array[iteration] = symbol;
    ++iteration;
  }

  if (close(file) < 0) {
    printf("Can\'t close file\n");
  }

  printf("we finished reading from task1_writer.c, size %d\nnow we will "
         "write it to shared memory\n",
         iteration);

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, iteration * sizeof(char),
                      0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, iteration * sizeof(char), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }
    }
  }

  if ((memory = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }

  for (int i = 0; i < iteration; ++i) {
    memory[i] = message[i];
  }

  printf("writer finished writing, size %ld\n", strlen(memory));

  if (shmdt(memory) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  return 0;
}
