#include "frac.h"
#include <cassert>
#include <iomanip>
#include <iostream>

frac::frac() : num(0), den(1) { this->simplify(); }
frac::frac(int64_t a) : num(a), den(1) { this->simplify(); }
frac::frac(int64_t n, int64_t d) : num(n), den(d) { this->simplify(); }

uint64_t frac::gcd(uint64_t a, uint64_t b) {
  uint64_t min = a < b ? a : b;
  uint64_t max = a > b ? a : b;
  if (min == 1 || min == 0)
    return 1;
  if (max % min == 0)
    return min;
  return frac::gcd(min, max % min);
}

frac frac::simplify() {
  if (this->num == 0 && this->den == 0)
    return *this;
  if (this->num == 0)
    this->den = 1;
  if (this->den == 0)
    this->num = 1;
  if (this->den < 0) {
    this->num *= -1;
    this->den *= -1;
  }
  uint64_t gcd =
      frac::gcd(static_cast<uint64_t>(this->num < 0 ? -this->num : this->num),
                static_cast<uint64_t>(this->den));
  this->num /= static_cast<int64_t>(gcd);
  this->den /= static_cast<int64_t>(gcd);
  return *this;
}

frac frac::operator+(const frac &other) const {
  return frac(this->num * other.den + other.num * this->den,
              this->den * other.den);
}

frac frac::operator-(const frac &other) const {
  return frac(this->num * other.den - other.num * this->den,
              this->den * other.den);
}

frac frac::operator*(const frac &other) const {
  return frac(this->num * other.num, this->den * other.den);
}

frac frac::operator/(const frac &other) const {
  return frac(this->num * other.den, other.den * this->num);
}

bool frac::operator<(const frac &other) const {
  return this->num * other.den < other.num * this->den;
}

bool frac::operator>(const frac &other) const {
  return this->num * other.den > other.num * this->den;
}

bool frac::operator<=(const frac &other) const {
  return this->num * other.den <= other.num * this->den;
}

bool frac::operator>=(const frac &other) const {
  return this->num * other.den >= other.num * this->den;
}

bool frac::operator==(const frac &other) const {
  return this->num == other.num && this->den == other.den;
}

frac::operator double() const {
  return static_cast<double>(this->num) / static_cast<double>(this->den);
}

std::ostream &operator<<(std::ostream &os, const frac &a) {
  if (a.num == 0 && a.den == 0)
    os << "nan";
  else if (a.den == 0)
    os << "inf";
  else if (a.den == 1)
    os << a.num;
  else
    os << a.num << '/' << a.den;
  return os;
}

int main() {
  std::cout << std::setw(6) << frac(2000, -10) << '\n';
  std::cout << std::setw(6) << frac(2001, 10) << '\n';
  std::cout << std::setw(6) << frac(2000, 0) << '\n';
  std::cout << std::setw(6) << frac(0, 0) << '\n';
  std::cout << std::setw(6) << frac(-2048, -48) << '\n';
  std::cout << std::setw(6) << frac(-462, 1071) << '\n';
  std::cout << std::setw(6) << frac(37, -999) << '\n';
  assert(frac(-1, -5) == frac(2, 10));
  assert(frac(-1, 0) == frac(2, 0));
  assert(frac(0, 2) == frac(0, -234));
  return 0;
}
