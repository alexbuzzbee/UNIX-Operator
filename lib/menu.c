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
#include "menu.h"
#include "util.h"

int showMenu(char *prefix, char *title, char **options, size_t numOptions) {
  int selection;
  clear();
  puts(prefix);
  puts("---");
  puts(title);
  for (size_t i = 0; i < numOptions - 1; i++) {
    printf("%i. %s\n", (int) i+1, options[i]);
  }
  printf("Make a selection[1-%i]: ", (int) numOptions);
  scanf("%i", &selection);
  return selection;
}
