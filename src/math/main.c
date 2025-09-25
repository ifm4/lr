#include <assert.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>

int64_t n, dx, d, s0;
void get_initial_conditions() {
  printf("Enter n, dx, d, s0: ");
  scanf(" %ld, %ld, %ld, %ld", &n, &dx, &d, &s0);
}

int64_t min(int64_t a, int64_t b) { return a < b ? a : b; }
int64_t max(int64_t a, int64_t b) { return a > b ? a : b; }

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

int64_t table_get_value(table_t table, size_t f, size_t x) {
  x /= dx;
  return x == 0 ? 0 : *(table.table + (f - 1) * table.rows + (x - 1));
}

int64_t get_opt(table_t table, int64_t s, size_t k) {
  if (s == 0)
    return 0;
  if (k == n)
    return table_get_value(table, k, (size_t)min(s, d));
  int64_t opt = 0;
  int64_t cur;
  for (int64_t _x = 0; _x <= min(s, d); _x += dx) {
    cur = table_get_value(table, (size_t)k, (size_t)_x) +
          get_opt(table, (int64_t)(s - _x), (size_t)(k + 1));
    opt = max(cur, opt);
  }
  return opt;
}

int main() {
  get_initial_conditions();
  assert(s0 != 0 && d != 0 && dx != 0);
  assert(s0 % dx == 0 && d % dx == 0);

  table_t table;
  table.columns = n;
  table.rows = min(d / dx, s0 / dx);

  table.table = (int64_t *)malloc(sizeof(int64_t) * table.rows * table.columns);
  assert(table.table != NULL);

  table_fill(table);
  table_print(table, "function's values:");

  int64_t result = get_opt(table, s0, 1);
  printf("f_max: %ld\n", result);

  free(table.table);
  table.table = NULL;
  assert(table.table == NULL);
  return 0;
}
