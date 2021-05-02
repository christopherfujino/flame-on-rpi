#include <stdio.h>

#include "my_application.h"

int main(int argc, char** argv) {
  printf("Hello from desktop C++ main!\n");
  g_autoptr(MyApplication) app = my_application_new();
  return g_application_run(G_APPLICATION(app), argc, argv);
}
