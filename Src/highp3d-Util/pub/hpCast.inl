#include "hpCast.h"
#include <utility>

namespace hp {
template<typename T>
inline unsigned Cast::ToUint(T item) noexcept {
  return static_cast<unsigned>(item);
}

template<typename T>
inline int Cast::ToInt(T item) noexcept {
  return static_cast<int>(item);
}

template<typename T>
inline float Cast::ToFloat(T item) noexcept {
  return static_cast<float>(item);
}

template<typename T, typename Out>
inline Out Cast::To(T item) {
  return static_cast<Out>(item);
}

template<typename T, typename U>
inline T Cast::Scast(U item) {
  return static_cast<T>(item);
}

template<typename T, typename U>
inline T Cast::Scast(U&& item) {
  return static_cast<T>(std::forward<U>(item));
}

template<typename T, typename U>
inline T Cast::Dcast(U item) {
  return dynamic_cast<T>(item);
}
template<typename T, typename U>
inline T Cast::Dcast(U&& item) {
  return dynamic_cast<T>(std::forward<U>(item));
}
template<typename T, typename U>
inline T Cast::Rcast(U item) {
  return reinterpret_cast<T>(item);
}
template<typename T, typename U>
inline T Cast::Rcast(U&& item) {
  return reinterpret_cast<T>(std::forward<U>(item));
}
template<typename T, typename U>
inline T Cast::Ccast(U item) {
  return const_cast<T>(item);
}
template<typename T, typename U>
inline T Cast::Ccast(U&& item) {
  return const_cast<T>(std::forward<U>(item));
}
}; // hp
