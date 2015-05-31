#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../lib/util.h"
#include "../../lib/menu.h"

int main(int argc, char *argv[]) {
  const char *const opts[] = {"Say Hello", "Exit"};
  while(true) {
    int selection = showMenu("", "App: Hello", (char **) opts, 2);
    switch(selection) {
      case 1:
        printf("Hello, world!\n");
        break;
      case 2:
        exit(0);
        break;
      default:
        break;
    }
  }
}
