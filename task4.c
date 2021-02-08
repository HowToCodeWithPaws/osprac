#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;
  pid =  fork();

  if (pid == -1) {
    printf("Something went terribly wrong\n");
    _exit(144);
  } else if (pid == 0) {

    pid  = getpid();
    printf("I am a child process, my pid = %d, and now i'm going to "
           "execute the tree command with parent directory and level 2.\n", (int)pid);

    int res = execle("/bin/tree", "/bin/tree", "../", "-L","2", 0, envp);

    if(res != 0){
      printf("Something went terribly wrong with execle\n");
      _exit(111);
    }
  } else {
    pid  = getpid();
    printf("I am a parent process, my pid = %d, and i will do nothing\n", (int)pid);
    wait(0);
  }

  return 0;
}
