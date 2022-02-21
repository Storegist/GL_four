#include "include/list.hpp"

#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void processdir(const struct dirent *dir) { puts(dir->d_name); }

/* This function shows how to get information from the /proc/<pid>
 * directory.  In this case it reads and filters on the owner
 * of the file (this is also the owner of the process)
 *
 * If you want to list ALL PID's, just remove the part
 * that check for the user.
 */
int filter(const struct dirent *dir) {
  uid_t user;
  struct stat dirinfo;
  int len = strlen(dir->d_name) + 7;
  char path[len];

  strcpy(path, "/proc/");
  strcat(path, dir->d_name);

  user = getuid();
  if (stat(path, &dirinfo) < 0) {
    perror("processdir() ==> stat()");
    exit(EXIT_FAILURE);
  }
  return !fnmatch("[1-9]*", dir->d_name, 0) && user == dirinfo.st_uid;
}
