#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
  printf("console arguments are: \n");
  for (int i = 0; i < argc; ++i) {
    printf("%d argument is %s\n", i, argv[i]);
  }

  printf("\nenvironment parameters are: \n");
  int i = 0;
  while (envp[i]!=NULL) {
    printf("%d parameter is %s\n", i, envp[i]);
    ++i;
  }

  printf("\nthat's all for today\n");
}