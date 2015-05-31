//UNIX Operator development version, simple menu-based interface for UNIX systems.
//Copyright (C) 2014  Alex Martin

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
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

int util_viewFile(const char *name) { // Invokes the current $PAGER on a file.
  char *pager = getenv("PAGER");
  if (pager == NULL) {
    pager = "/bin/less";
  }
  int pid = fork();
  if (pid == 0) {
    execl(pager, pager, name, (void *) NULL);
  } else if (pid == -1) { // Backup black magic.
    return 1;
  } else {
    int status;
    wait(&status);
  }
  return 0;
}

int util_shellCmd(const char *command) { // Executes a shell command using the current $SHELL.
  char *shell = getenv("SHELL");
  if (shell == NULL) {
    shell = "/bin/bash";
  }
  int pid = fork();
  if (pid == 0) {
    execl(shell, shell, "-c", command, (void *) NULL);
  } else if (pid == -1) { // Backup black magic, if fork() fails.
    return 1;
  } else {
    int status;
    wait(&status);
  }
  return 0;
}

int clear() {
  int pid = fork();
  if (pid == 0) {
    execlp("clear", "clear", (void *) NULL);
  } else if (pid == -1) {
    return 1;
  } else {
    int status;
    wait(&status);
  }
  return 0;
}
