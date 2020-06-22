#include "../pub/hpString.h"

namespace hp {
template <typename T,
  typename std::enable_if_t<std::is_integral<T>::value>*>
  inline hpString hpString::to_hpString(T param) {

  return hpString();
}

template <typename T,
  typename std::enable_if_t<std::is_floating_point<T>::value>*>
  inline hpString hpString::to_hpString(T param) {
  return hpString();
}

template <typename T,
  typename std::enable_if_t<std::is_integral<T>::value>*>
  inline const char* hpString::to_hpString(T param) {}

template <typename T,
  typename std::enable_if_t<std::is_floating_point<T>::value>*>
  inline const char* hpString::to_hpString(T param) {}

template <typename T,
  typename std::enable_if_t<std::is_integral<T>::value>*>
  inline T hpString::to_T(const hpString& str) {
  return T();
}

template <typename T,
  typename std::enable_if_t<std::is_floating_point<T>::value>*>
  inline T hpString::to_T(const hpString& str) {
  return T();
}

template <typename T,
  typename std::enable_if_t<std::is_integral<T>::value>*>
  inline T hpString::to_T(hpString&& str) {
  return T();
}

template <typename T,
  typename std::enable_if_t<std::is_floating_point<T>::value>*>
  inline T hpString::to_T(hpString&& str) {
  return T();
}
};  // namespace hp
