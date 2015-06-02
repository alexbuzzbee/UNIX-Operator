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
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/util.h"
#include "lib/menu.h"

int mainMenu();
int mainMenu_opt_help();
int mainMenu_opt_about();
int mainMenu_opt_apps();
int apps_opt_cmdline();
void shutdown();

int mainMenu_opt_help() {
  util_viewFile("help.txt");
  return 0;
}

int mainMenu_opt_about() {
  const char *const opts[] = {"View GNU General Public License, Version 3", "View credits", "Back"};
  while(true) {
    int selection = showMenu("Version 0.3-dev by Alex Martin and GitHub contributors.\nCopyright (C) 2014 Alex Martin.\nThis program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\nUNIX Operator\nVersion 0.4-dev by Alex Martin and GitHub contributors\nCopyright (C) 2014 Alex Martin.", "About UNIX Operator", (char **) opts, 3);
    switch(selection) {
      case 1:
        util_viewFile("LICENSE");
        break;
      case 2:
        util_viewFile("credits.txt");
        break;
      default:
        return 0;
        break;
    }
  }
}

int apps_opt_cmdline() {
  char cmd[128] = "";
  char *shell = getenv("SHELL");
  if (shell == NULL) {
    shell = "/bin/bash";
  }
  printf("Enter a command to execute using %s: ", shell);
  scanf(" %[^\n]", (char *) &cmd);
  util_shellCmd((const char *) &cmd);
  return 0;
}

int apps_opt_uop() {
  char cwd[128] = "";
  char app[128] = "";
  getcwd((char *) &cwd, sizeof(cwd)/sizeof(cwd[0])); // Get the working directory.
  char cmd[128] = "ls -l | egrep 'wx|-x' | grep -v '^d'"; // Checks execute permission bit on files (but not directories) in current directory.
  util_shellCmd((char *) &cmd);
  printf("Enter the name of an application to run: ");
  scanf(" %[^\n]", (char *) &app);
  int pid = fork(); // Fork/exec the application.
  if (pid == 0) {
    char path[128] = "";
    strcat((char *) &path, (char *) &cwd);
    strcat((char *) &path, "/"); // Acquire the application's absolute path.
    strcat((char *) &path, (char *) &app);
    printf("Running %s...", (char *) &path);
    execl((char *) &path, (char *) &path, (void *) NULL); // Exec to the application.
  } else if (pid == -1) {
    return 1; // Error.
  } else {
    int status;
    wait(&status);
  }
  return 0;
}

int mainMenu_opt_apps() {
  const char *const opts[] = {"UNIX Operator applications >", "Command-line applications >", "Back"};
  int selection = showMenu("", "Applications", (char **) opts, 3);
  switch(selection) {
    case 1:
      apps_opt_uop();
      sleep(1);
      break;
    case 2:
      apps_opt_cmdline();
      break;
    default:
      break;
  }
  return 0;
}

void shutdown() {
  exit(0);
}

int mainMenu() {
  const char *const opts[] = {"Help", "About >", "Applications >", "Exit"};
  while(true) {
    int selection = showMenu("", "UOP main menu", (char **) opts, 4);
    switch(selection) {
      case 1:
        mainMenu_opt_help();
        break;
      case 2:
        mainMenu_opt_about();
        break;
      case 3:
        mainMenu_opt_apps();
        break;
      case 4:
        shutdown();
        break;
      default:
        mainMenu_opt_help();
        break;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  fprintf(stderr, "%s: Warning: The C version of UNIX Operator is not ready to be used.\n", argv[0]);
  //exit(1); // Program will terminate with an error, so anything below here will not run.
  mainMenu();
  return 0;
}
