#include "../pub/hpASCII.h"

namespace hp {
unsigned
hpASCII::CharToUint(char c) noexcept {
  return (unsigned)c;
}

float
hpASCII::Convert_Float(const char* c) noexcept {
  float result = 0.0f;
  unsigned length = 0u;
  while (*c++ != '\0') ++length;
  c -= (length + 1);

  unsigned pusher = 0u;
  bool under = false;
  while (*c != '\0') {
    unsigned num = static_cast<int>(*c);
    unsigned multiplier = 1u;
    if (*c == '.') {
      under = true;
      multiplier = 1u;
      pusher = 1u;
    }

    if (hpASCII::Contain_Number(num)) {
      for (unsigned i = 0; i < pusher; ++i)
        multiplier *= 10;

      if (!under) {
        result += static_cast<float>(((num - 48) * multiplier));
        ++pusher;
      }
      else if (under) {
        float n = (static_cast<float>(num - 48) / static_cast<float>(multiplier));
        result += n;
        ++pusher;
      }
      multiplier = 1u;
    }
    ++c;
  }
  return result;
}

float
hpASCII::Convert_Int(const char* c) noexcept {
  return 0.0f;
}

bool
hpASCII::Contain_Uppercast(char c) noexcept {
  bool isContain = false;
  for (unsigned i = 0; i < hpASCII::uppercase_alphabet_size; ++i) {
    isContain = (hpASCII::uppercase_alphabet_uint[i] == c);
    if (isContain) break;
  }
  return isContain;
}

bool
hpASCII::Contain_Lowercase(char c) noexcept {
  bool isContain = false;
  for (unsigned i = 0; i < hpASCII::lowercase_alphabet_size; ++i) {
    isContain = (hpASCII::lowercase_alphabet_uint[i] == c);
    if (isContain) break;
  }
  return isContain;
}

bool
hpASCII::Contain_Number(char c) noexcept {
  bool isContain = false;
  for (unsigned i = 0; i < hpASCII::numbers_size; ++i) {
    isContain = (hpASCII::numbers_uint[i] == c);
    if (isContain) break;
  }
  return isContain;
}
};
