#pragma once

#include "hpMacro.h"

namespace hp {
class hpRandom final {

  DELETE_CDTOR_COPY_MOVE(hpRandom)

public:
  static void set_seed(long seed = 0);

  static int rand_int() noexcept;
  static unsigned rand_unsigned() noexcept;
  static float rand_float() noexcept;
  static double rand_double() noexcept;

  static int rand_range_int(int min, int max) noexcept;
  static unsigned rand_range_unsigned(unsigned min, unsigned max) noexcept;
  static float rand_range_float(float min, float max) noexcept;
  static double rand_range_double(double min, double max) noexcept;

private:
  static long current_seed;
};
};
