#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
  int size = 1982;
  char *memory;
  int shmid;
  int new = 1;
  char pathname[] = "oscourse/05-4.c";
  key_t key;

  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, size * sizeof(char), 0666 | IPC_EXCL)) <
      0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, size * sizeof(char), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
      }
    }
  }

  if ((memory = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }

  printf("reading: %s\n", memory);

  if (shmdt(memory) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  if (shmctl(shmid, IPC_RMID, NULL)) {
    printf("Can't delete shared memory\n");
    exit(-1);
  }

  return 0;
}
