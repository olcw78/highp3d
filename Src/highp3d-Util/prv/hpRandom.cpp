#include "../pub/hpRandom.h"
#include <ctime>
#include <cstdlib>

namespace hp {
int
hpRandom::RandomInt(int seed) noexcept {
  srand(seed != 0 ? seed : static_cast<unsigned>(time(nullptr)));
  return rand();
}

unsigned
hpRandom::RandomUnsigned(int seed) noexcept {
  return static_cast<unsigned>(hpRandom::RandomInt(seed));
}

float
hpRandom::RandomFloat(int seed) noexcept {
  return static_cast<float>(hpRandom::RandomInt(seed));
}

double
hpRandom::RandomDouble(int seed) noexcept {
  return static_cast<double>(hpRandom::RandomInt(seed));
}

int
hpRandom::RandomRange(int min, int max, int seed) noexcept {
  int res = 0;
  while (res <= max && res >= min) {
    res = hpRandom::RandomInt(seed);
  }
  return res;
}

unsigned
hpRandom::RandomRangeUnsigned(unsigned min, unsigned max, int seed) noexcept {
  unsigned res = 0u;
  while (res <= max && res >= min) {
    res = hpRandom::RandomUnsigned(seed);
  }
  return res;
}

float
hpRandom::RandomRangeFloat(float min, float max, int seed) noexcept {
  float res = 0.0f;
  while (res <= max && res >= min) {
    res = hpRandom::RandomFloat(seed);
  }
  return res;
}

double
hpRandom::RandomRangeDouble(double min, double max, int seed) noexcept {
  double res = 0.0;
  while (res <= max && res >= min) {
    res = hpRandom::RandomDouble(seed);
  }
  return res;
}
};  // namespace hp
