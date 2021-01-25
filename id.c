#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int uid = getuid();
    int gid = getgid();
    printf("user id = %d\ngroup id = %d\n", uid, gid);

return 0;
}