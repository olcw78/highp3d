#pragma once

#include "hpMacro.h"

namespace hp {
class Cast final {
  DELETE_CDTOR_COPY_MOVE(Cast)

public:
  template <typename T>
  static unsigned ToUint(T item) noexcept;

  template <typename T>
  static int ToInt(T item) noexcept;

  template <typename T>
  static float ToFloat(T item) noexcept;

  template <typename T, typename Out>
  static Out To(T item);

  template <typename T, typename U>
  static T Scast(U item);

  template <typename T, typename U>
  static T Scast(U&& item);

  template <typename T, typename U>
  static T Dcast(U item);

  template <typename T, typename U>
  static T Dcast(U&& item);

  template <typename T, typename U>
  static T Rcast(U item);

  template <typename T, typename U>
  static T Rcast(U&& item);

  template <typename T, typename U>
  static T Ccast(U item);

  template <typename T, typename U>
  static T Ccast(U&& item);
};
}; // hp

#include "hpCast.inl"
