#ifndef FRAC_H
#define FRAC_H

#include <cstdint>

struct frac {
  int64_t num;
  int64_t den;

  frac();
  frac(int64_t);
  frac(int64_t, int64_t);

  static uint64_t gcd(uint64_t, uint64_t);
  frac simplify();

  frac operator+(const frac &) const;
  frac operator-(const frac &) const;
  frac operator*(const frac &) const;
  frac operator/(const frac &) const;
  bool operator<(const frac &) const;
  bool operator>(const frac &) const;
  bool operator<=(const frac &) const;
  bool operator>=(const frac &) const;
  bool operator==(const frac &) const;
  explicit operator double() const;
};

#endif
