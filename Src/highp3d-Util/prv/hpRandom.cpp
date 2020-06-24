#include "../pub/hpRandom.h"
#include <ctime>
#include <cstdlib>

namespace hp {

#pragma region static fields initialisation
long hpRandom::current_seed = 0l;
#pragma endregion

void hpRandom::set_seed(long seed /*= 0*/) {
  hpRandom::current_seed = seed;
  srand(seed != 0 ? seed : static_cast<unsigned>(time(nullptr)));
}

int
hpRandom::rand_int() noexcept {
  return rand();
}

unsigned
hpRandom::rand_unsigned() noexcept {
  return static_cast<unsigned>(rand());
}

float
hpRandom::rand_float() noexcept {
  return static_cast<float>(rand());
}

double
hpRandom::rand_double() noexcept {
  return static_cast<double>(rand());
}

int
hpRandom::rand_range_int(int min,
                         int max) noexcept {
  int res = 0;
  while (res <= max && res >= min) {
    res = hpRandom::rand_int();
  }
  return res;
}

unsigned
hpRandom::rand_range_unsigned(unsigned min,
                              unsigned max) noexcept {
  unsigned res = 0u;
  while (res <= max && res >= min) {
    res = hpRandom::rand_unsigned();
  }
  return res;
}

float
hpRandom::rand_range_float(float min,
                           float max) noexcept {
  float res = 0.0f;
  while (res <= max && res >= min) {
    res = hpRandom::rand_float();
  }
  return res;
}

double
hpRandom::rand_range_double(double min,
                            double max) noexcept {
  double res = 0.0;
  while (res <= max && res >= min) {
    res = hpRandom::rand_double();
  }
  return res;
}

};  // namespace hp
