#pragma once

#include "hpASCII.h"
#include <ostream>
#include <utility>

namespace hp {
class hpString final {
public:
  hpString() noexcept;
  hpString(const char* str) noexcept;
  hpString(const char* str, unsigned capacity) noexcept;
  hpString(char str) noexcept;

  ~hpString() noexcept;
  hpString(const hpString& cpy) noexcept;
  hpString(hpString&& mov) noexcept;
  hpString& operator=(const hpString& cpy) noexcept;
  hpString& operator=(hpString&& mov) noexcept;

  bool operator<(const hpString& ref) const noexcept;
  bool operator>(const hpString& ref) const noexcept;
  bool operator==(const hpString& comp) const noexcept;
  void operator<<(const hpString& add) noexcept;
  void operator<<(const char* add) noexcept;
  void operator<<(char add) noexcept;

  friend std::ostream& operator<<(std::ostream& ostr, hpString& str);

  char operator[](int index) noexcept;
  size_t operator()(const hpString& cpy) noexcept;

  // Factories.
public:
  static hpString make_new() noexcept;
  static hpString make_new(const char* str) noexcept;
  static hpString make_new(const char* str, unsigned capacity) noexcept;

  // Util functions.
public:
  static bool is_empty(const hpString& ref) noexcept;
  static unsigned len(const char* str) noexcept;
  static unsigned len(const hpString& ref) noexcept;
  static void append(char* target, unsigned orig_len, const char* substr) noexcept;
  static void append(hpString& ref, const char* substr);
  static void append(hpString& ref, char c);
  static void append(hpString& ref, const hpString& subref);
  static bool equal(const char* str1, const char* str2) noexcept;
  static bool equal(const hpString& str1, const hpString& str2);
  static bool contain(const char* str, const char* substr);
  static bool contain(const char* str, char c) noexcept;
  static bool contain(const hpString& str, const hpString& substr);
  static bool contain(const hpString& str, const char* substr);
  static const char* copy(char* dest, const char* src);
  static const char* concat(char* dest, const char* src);
  static const char* concat(const char* str1, const char* str2);

  template <typename T,
    typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    static hpString to_hpString(T param);

  template <typename T,
    typename std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    static hpString to_hpString(T param);

  template <typename T,
    typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    static const char* to_hpString(T param);

  template <typename T,
    typename std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    static const char* to_hpString(T param);

  template <typename T,
    typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    static T to_T(const hpString& str);

  template <typename T,
    typename std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    static T to_T(const hpString& str);

  template <typename T,
    typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    static T to_T(hpString&& str);

  template <typename T,
    typename std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    static T to_T(hpString&& str);

  // Member functions.
public:
  bool empty() const noexcept;
  const char* reverse();
  bool reserve(unsigned new_size);
  void reset(const char* str);
  bool equal(const char* str);
  bool eqaul(const hpString& str);

  hpString& append(const hpString& ref);
  hpString& append(hpString&& mov);
  hpString& append(const char* str);
  hpString& append(char c);

  hpString& insert(unsigned location, hpString&& mov);
  hpString& insert(unsigned location, const hpString& cpy);
  hpString& insert(unsigned location, const char* str);
  hpString& insert(unsigned location, char c);

  void copy_from(hpString& from);
  void copy_from(const char* str);
  void copy_from(char c);

  void copy_to(hpString& to);  
  void copy_to(char* str);

  // Util member functions.
public:
  void print() const noexcept;
  void println() const noexcept;
  void print_err() const noexcept;
  void println_err() const noexcept;
  const char* get_c_str() const noexcept;
  char* get_editable_c_str() noexcept;
  void set_str(const char* str);
  unsigned get_len() const noexcept;
  void setLength(unsigned length);
  unsigned get_cap() const noexcept;
  void set_cap(unsigned cap);

private:
  static char* alloc_new_str(unsigned new_size);
  static char* alloc_new_char(char c);
  static char* alloc_new_str(const char* orig);
  static char* alloc_new_str(const char* orig, unsigned new_size);

  // Member variables.
private:
  char* str_body = nullptr;
  unsigned length = 0;
  unsigned capacity = 0;
};
};  // namespace hp

std::ostream& operator<<(std::ostream& ostr, hp::hpString& str);

#include "../prv/hpString.inl"
