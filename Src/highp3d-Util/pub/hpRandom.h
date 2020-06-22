#pragma once

#include "hpMacro.h"

namespace hp {
class hpRandom final {
  DELETE_CDTOR_COPY_MOVE(hpRandom)

public:
  static int RandomInt(int seed = 0) noexcept;
  static unsigned RandomUnsigned(int seed = 0) noexcept;
  static float RandomFloat(int seed = 0) noexcept;
  static double RandomDouble(int seed = 0) noexcept;

  static int RandomRange(int min = 0, int max = 0, int seed = 0) noexcept;
  static unsigned RandomRangeUnsigned(unsigned min = 0u,
                                      unsigned max = 0u, int seed = 0) noexcept;
  static float RandomRangeFloat(float min = 0.0f, float max = 0.0f, int seed = 0) noexcept;
  static double RandomRangeDouble(double min = 0.0, double max = 0.0, int seed = 0) noexcept;
};
};
