#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "include/list.hpp"

int main() {
  struct dirent **namelist;
  int n;

  n = scandir("/proc", &namelist, filter, 0);
  if (n < 0)
    perror("Not enough memory.");
  else {
    while (n--) {
      processdir(namelist[n]);
      free(namelist[n]);
    }
    free(namelist);
  }
  return 0;
}
