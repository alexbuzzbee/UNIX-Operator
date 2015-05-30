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
    int selection = showMenu("Version 0.3-dev by Alex Martin and GitHub contributors.\nCopyright (C) 2014 Alex Martin.\nThis program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\nUNIX Operator\nVersion 0.3-dev by Alex Martin and GitHub contributors\nCopyright (C) 2014 Alex Martin.", "About UNIX Operator", (char **) opts, 3);
    switch(selection) {
      case 1:
        util_viewFile("gpl-3.0.txt");
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
  if (getenv("SHELL") == NULL) {
    puts("Error: Shell not specified in current environment. Abort.");
    return 1;
  }
  printf("Enter a command to execute using %s: ", getenv("SHELL"));
  scanf(" %[^\n]", (char *) &cmd);
  system((const char *) &cmd); // Actually not black magic, since executing a command using the current $SHELL is exactly what we want.
  return 0;
}

int mainMenu_opt_apps() {
  const char *const opts[] = {"UNIX Operator applications >", "Command-line applications >", "Back"};
  int selection = showMenu("", "Applications", (char **) opts, 3);
  switch(selection) {
    case 1:
      puts("Stub for UOP apps.");
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
