#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "util.h"

#define BLOCKSIZE 256

// Loads a text file using POSIX system calls.
char *util_loadFile(const char *path) {
  char *buff;
  char *part;
  int f;
  int bytesRead;
  off_t size;
  f = open(path, O_RDONLY); // Open file.
  if (f == -1) {
    return NULL;
  }
  size = lseek(f, 0, SEEK_END); // Get file size.
  if (size == -1) {
    close(f);
    return NULL;
  }
  if (lseek(f, 0, SEEK_SET) == -1) {
    close(f);
    return NULL;
  }
  buff = (char *) malloc(size + 1); // Allocate buffers.
  part = (char *) malloc(BLOCKSIZE + 1);
  buff[0] = '\0'; // Initialize first byte to a zero, to make string functions work.
  do {
    bytesRead = read(f, part, BLOCKSIZE);
    if (bytesRead < 0) {
      free(buff);
      free(part);
      close(f);
      return NULL;
    }
    part[bytesRead] = '\0'; // Add a zero to the end.
    strcat(buff, part); // Append part to buffer.
  } while (bytesRead != 0);
  free(part);
  close(f);
  return buff;
}

void util_viewFile(const char *name) { // Uses black magic to invoke less on a file.
  char cmd[128] = {'l', 'e', 's', 's', ' '};
  strcat(cmd, name);
  system((const char *) cmd);
}

void clear() {
  int pid = fork();
  if (pid == 0) {
    execlp("clear", "clear");
  } else if (pid == -1) {
    system("clear"); // Backup black magic.
  } else {
    wait(&pid);
  }
}
