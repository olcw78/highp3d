#pragma once

#include "hpMacro.h"

namespace hp {
class hpRandom final {
  DELETE_CDTOR_COPY_MOVE(hpRandom)

public:
  static int rand_int(int seed = 0) noexcept;
  static unsigned rand_unsigned(int seed = 0) noexcept;
  static float rand_float(int seed = 0) noexcept;
  static double rand_double(int seed = 0) noexcept;

  static int rand_range_int(int min = 0, int max = 0, int seed = 0) noexcept;
  static unsigned rand_range_unsigned(unsigned min = 0u,
                                      unsigned max = 0u, int seed = 0) noexcept;
  static float rand_range_float(float min = 0.0f, float max = 0.0f, int seed = 0) noexcept;
  static double rand_range_double(double min = 0.0, double max = 0.0, int seed = 0) noexcept;
};
};
