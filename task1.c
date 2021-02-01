#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  pid_t pid, ppid;

  pid  = getpid();
  ppid = getppid();

  printf("Current process ID: %d,\nCurrent process parent ID: %d\n", (int)pid, (int)ppid);

  return 0;
}

/// При многократном запуске pid возрастает, но ppid не изменяется. это связано с тем,
/// что при создании процессов-детей им дается новое значение из свободных и больших текущего.