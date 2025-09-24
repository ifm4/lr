#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

long n, dx, d, s0;

void get_initial_conditions() {
  printf("Enter n, dx, d, s0: ");
  scanf(" %ld, %ld, %ld, %ld", &n, &dx, &d, &s0);
}

typedef struct table_t {
  int64_t *table;
  size_t rows;
  size_t columns;
} table_t;

void table_fill(table_t table) {
  for (int c = 1; c <= table.columns; c++)
    for (int r = 1; r <= table.rows; r++) {
      printf("Enter f%d(%ld): ", c, r * dx);
      scanf(" %ld", table.table + (c - 1) * table.rows + (r - 1));
    }
}

void table_print(table_t table, const char *label) {
  printf("%s\n", label);
  for (int r = 1; r <= table.rows; r++) {
    for (int c = 1; c <= table.columns; c++)
      printf("%ld\t", *(table.table + (c - 1) * table.rows + (r - 1)));
    printf("\n");
  }
}

int64_t table_get(table_t table, size_t f, size_t x_normalized) {
  return *(table.table + (f - 1) * table.rows + (x_normalized - 1));
}

long min(long a, long b) { return a < b ? a : b; }

int64_t f_opt(table_t table, int64_t s, size_t k) {
  if (s == 0)
    return 0;
  if (k == n)
    return table_get(table, k, s / dx);
  int64_t val;
  int64_t opt = 0;
  for (int i = 0; i < min(s / dx, d / dx); i++) {
    val = table_get(table, k, (size_t)i) + f_opt(table, s - i * dx, k + 1);
    opt = opt < val ? val : opt;
  }
  ++k;
  return opt;
}

int main() {
  get_initial_conditions();
  table_t table;
  table.columns = n;
  table.rows = min(d / dx, s0 / dx);
  table.table = (int64_t *)malloc(sizeof(int64_t) * table.rows * table.columns);
  if (table.table == NULL)
    return 1;
  table_fill(table);
  table_print(table, "function's values:");
  int64_t opt = f_opt(table, s0, 1);
  printf("opt: %ld\n", opt);
  free(table.table);
}
