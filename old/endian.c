#include <stdio.h>

int main() {
  int i = 0x01020304;
  int *pi = &i;
  char *ci = (char *)pi + 1;
  printf("i: 0x%08x; c: 0x%02x\n", i, *ci);
  return 42;
}
