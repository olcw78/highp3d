#pragma once

#include "hpMacro.h"

namespace hp {
class hpASCII final {
  DELETE_CDTOR_COPY_MOVE(hpASCII)

public:
  static constexpr unsigned lowercase_alphabet_uint[]{
      97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
      109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
      121, 122
  };

  static constexpr unsigned lowercase_alphabet_size = sizeof(hpASCII::lowercase_alphabet_uint) / sizeof(unsigned);

  static constexpr unsigned uppercase_alphabet_uint[]{
      65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
      81, 82, 83, 84, 85, 86, 87, 88, 89, 90
  };

  static constexpr unsigned uppercase_alphabet_size = sizeof(hpASCII::uppercase_alphabet_uint) / sizeof(unsigned);

  static constexpr unsigned numbers_uint[]{
      48, 49, 50, 51, 52, 53, 54, 55, 56, 57
  };

  static constexpr unsigned numbers_size = sizeof(hpASCII::numbers_uint) / sizeof(unsigned);

  static constexpr unsigned space_uint = 32;

  static unsigned CharToUint(char c) noexcept;

  static float Convert_Float(const char* c) noexcept;

  static float Convert_Int(const char* c) noexcept;

  static bool Contain_Uppercast(char c) noexcept;

  static bool Contain_Lowercase(char c) noexcept;

  static bool Contain_Number(char c) noexcept;
};
}; // hp
