#include "../pub/hpRandom.h"
#include <ctime>
#include <cstdlib>

namespace hp {
int
hpRandom::rand_int(int seed) noexcept {
  srand(seed != 0 ? seed : static_cast<unsigned>(time(nullptr)));
  return rand();
}

unsigned
hpRandom::rand_unsigned(int seed) noexcept {
  return static_cast<unsigned>(hpRandom::rand_int(seed));
}

float
hpRandom::rand_float(int seed) noexcept {
  return static_cast<float>(hpRandom::rand_int(seed));
}

double
hpRandom::rand_double(int seed) noexcept {
  return static_cast<double>(hpRandom::rand_int(seed));
}

int
hpRandom::rand_range_int(int min, int max, int seed) noexcept {
  int res = 0;
  while (res <= max && res >= min) {
    res = hpRandom::rand_int(seed);
  }
  return res;
}

unsigned
hpRandom::rand_range_unsigned(unsigned min, unsigned max, int seed) noexcept {
  unsigned res = 0u;
  while (res <= max && res >= min) {
    res = hpRandom::rand_unsigned(seed);
  }
  return res;
}

float
hpRandom::rand_range_float(float min, float max, int seed) noexcept {
  float res = 0.0f;
  while (res <= max && res >= min) {
    res = hpRandom::rand_float(seed);
  }
  return res;
}

double
hpRandom::rand_range_double(double min, double max, int seed) noexcept {
  double res = 0.0;
  while (res <= max && res >= min) {
    res = hpRandom::rand_double(seed);
  }
  return res;
}
};  // namespace hp
