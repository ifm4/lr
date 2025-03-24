// #include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const uint8_t max_matrix_size = 10;
struct square_matrix_t {
  double *arr;
  uint8_t size;
};

int main() {
  srand(time(NULL));
  double m[max_matrix_size * max_matrix_size];
  printf("%ld %d %d\n", sizeof(m), RAND_MAX, rand() % 10);
  int a = 80;
  printf("\n|%*s|\n", a, "Hello, world!");
  return 0;
}
