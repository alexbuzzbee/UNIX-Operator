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
#include "util.h"

void mainMenu();
void mainMenu_opt_help();
int mainMenu_opt_about();
void mainMenu_opt_apps();
void shutdown();

void mainMenu_opt_help() {
  util_viewFile("help.txt");
}

int mainMenu_opt_about() {
  int selection;
  while(true) {
    clear();
    puts("About UNIX Operator");
    puts("Version 0.2-dev by Alex Martin and GitHub contributors.");
    puts("Copyright (C) 2014 Alex Martin.");
    puts("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.");
    puts("---");
    puts("1. View GNU General Public License");
    puts("2. View credits");
    puts("3. Back");
    printf("Make a selection[1,2,3]: ");
    scanf("%i", &selection);
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

void mainMenu_opt_apps() {
  int selection;
  clear();
  puts("Applications");
  puts("1. UNIX Operator applications >");
  puts("2. Command-line applications >");
  puts("3. Back");
  printf("Make a selection[1,2,3]: ");
  scanf("%i", &selection);
  switch(selection) {
    case 1:
      puts("Stub for UOP apps.");
      sleep(1);
      break;
    case 2:
      puts("Stub for CLI apps.");
      sleep(1);
      break;
    default:
      break;
  }
}

void shutdown() {
  exit(0);
}

void mainMenu() {
  int selection;
  while(true) {
    clear();
    puts("UOP main menu");
    puts("1. Help");
    puts("2. About >");
    puts("3. Applications >");
    puts("4. Exit");
    printf("Make a selection[1,2,3,4]: ");
    scanf("%i", &selection);
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
}

int main(int argc, char *argv[]) {
  fprintf(stderr, "%s: Warning: The C version of UNIX Operator is not ready to be used.\n", argv[0]);
  //exit(1); // Program will terminate with an error, so anything below here will not run.
  mainMenu();
  return 0;
}
