#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;
  
  int a = 0;

  pid =  fork();
    
  if (pid == -1) {
    printf("Something went terribly wrong");
    _exit(144);
} else if (pid == 0) {
    a = a+1;
    
    pid  = getpid();
    ppid = getppid();
  
    printf("I am child-process, my pid = %d, my ppid = %d, result = %d, the action was ++a\n", (int)pid, (int)ppid, a);
} else {
    a = a-1;
    
    pid  = getpid();
    ppid = getppid();
    
    printf("I am parent-process, my pid = %d, my ppid = %d, result = %d, the action was --a\n", (int)pid, (int)ppid, a);
}

  return 0;
}
