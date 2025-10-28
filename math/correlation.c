#include <math.h>
#include <stdio.h>
#define MAX_SET_SIZE (128)

size_t get_set_size() {
  size_t size;
  do {
    printf("Enter set size: ");
    scanf("%ld", &size);
  } while (size > MAX_SET_SIZE);
  return size == 0 ? MAX_SET_SIZE : size;
}

void enter_set(double *set, size_t n, const char *name) {
  for (int i = 0; i < n; ++i) {
    printf("Enter %s[%d]: ", name, i);
    scanf("%lf", set + i);
  }
}

double mean(double *set, size_t n) {
  double mean = 0;
  for (int i = 0; i < n; ++i)
    mean += set[i];
  return mean / n;
}

double std_dev(double *set, size_t n) {
  double sum = 0;
  double avg = mean(set, n);
  for (int i = 0; i < n; ++i)
    sum += pow((set[i] - avg), 2);
  return sqrt(sum / n);
}

double covariance(double *set_a, double *set_b, size_t n) {
  double sum = 0;
  double avg_a = mean(set_a, n);
  double avg_b = mean(set_b, n);
  for (int i = 0; i < n; ++i)
    sum += (set_a[i] - avg_a) * (set_b[i] - avg_b);
  return sum / pow(n, 2);
}

double correlation(double *set_a, double *set_b, size_t n) {
  return covariance(set_a, set_b, n) / (std_dev(set_a, n) * std_dev(set_b, n));
}

int main() {
  double x[MAX_SET_SIZE];
  double y[MAX_SET_SIZE];

  size_t n = get_set_size();
  enter_set(x, n, "x");
  enter_set(y, n, "y");

  double r = correlation(x, y, n);
  printf("r = %lf\n", r);
}
