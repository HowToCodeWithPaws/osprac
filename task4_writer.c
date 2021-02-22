#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  size_t size;
  //пришлось слегка поменять адрес, потому что wsl не дружил с тем что было
  char name[] = "/tmp/aaa.fifo";

  (void)umask(0);

  printf("IMPORTANT: fifo is created in /tmp/aaa.fifo because "
         "it didn't work on my laptop's wsl otherwise\n");

  if (mknod(name, S_IFIFO | 0666, 0) < 0) {
    printf("Can\'t create FIFO\n");
    exit(-1);
  }

  /* Writer program
   * предположим нас устраивает блокировка (хотя звучит вообще говоря неприято),
   * получать ошибку более неприятно, поэтому не будем добавлять флаг O_NDELAY
   * вместо этого для обмена информацией нужно запустить параллельно программы
   * writer и reader (либо в консоли с помощью & после команды запуска, либо
   * через два разных терминала) и дать writer-y повисеть до появления ридера
   * честно говоря не понятно, так ли нужно выполнять задание, потому что
   * это не "написать две программы", а "запустить два куска одной программы
   * определенным образом", короче говоря очень интересно
   * */

  if ((fd = open(name, O_WRONLY)) < 0) {
    printf("Can\'t open FIFO for writing\n");
    exit(-1);
  }

  size = write(fd, "Hello, world!", 14);

  if (size != 14) {
    printf("Can\'t write all string to FIFO\n");
    exit(-1);
  }

  if (close(fd) < 0) {
    printf("Can\'t close FIFO\n");
    exit(-1);
  }

  printf("Writer exits, message is written\n");

  return 0;
}
