#include "../pub/hpString.h"
#include <iostream>
#include <cstdlib>

namespace hp {
hpString::hpString() noexcept {

  //
}

hpString::~hpString() noexcept {
  /*do {
    delete mStr;
    mStr = nullptr;
  } while (mStr != nullptr);*/
}

hpString::hpString(const char* str) noexcept {
  const unsigned strlen = hpString::len(str);

  if (strlen == 0u) {
    return;
  }

  if (capacity < strlen) {
    str_body = hpString::alloc_new_str(strlen);
    capacity = strlen;
    length = strlen;
  }

  for (unsigned i = 0; i < length; ++i) {
    str_body[i] = str[i];
  }
  length = strlen;
}

hpString::hpString(const char* str, unsigned capacity) noexcept {
  const unsigned fwd_len = hpString::len(str);
  if (fwd_len == 0u) return;
  str_body = hpString::alloc_new_str(fwd_len);
  capacity = capacity;
  length = fwd_len;
  memcpy(str_body, str, sizeof(length));
}

hpString::hpString(char new_contents) noexcept {
  str_body = hpString::alloc_new_str(1);
  str_body[0] = new_contents;
  capacity = length = 1u;
}

hpString::hpString(const hpString& cpy) noexcept {
  if (capacity < cpy.length) {
    str_body = hpString::alloc_new_str(cpy.length);
    capacity = cpy.length;
    length = cpy.length;
  }

  hpString::copy(str_body, cpy.str_body);
}

hpString::hpString(hpString&& mov) noexcept { *this = std::move(mov); }

hpString& hpString::operator=(const hpString& cpy) noexcept {
  length = cpy.length;

  if (!str_body) {
    str_body = hpString::alloc_new_str(length);
  }

  if (length < cpy.length) {
    str_body = hpString::alloc_new_str(length);
  }

  hpString::copy(str_body, cpy.str_body);
  return *this;
}

hpString& hpString::operator=(hpString&& mov) noexcept {
  str_body = std::move(mov.str_body);
  length = mov.length;
  capacity = mov.capacity;
  return *this;
}

bool hpString::is_empty(const hpString& ref) noexcept {
  return len(ref.str_body) == 0 || ref.str_body == nullptr;
}

unsigned hpString::len(const char* str) noexcept {
  if (str == nullptr || str == "") {
    return 0u;
  }
  unsigned length = 0u;
  while (*(str++)) ++length;
  return length;
}

unsigned hpString::len(const hpString& ref) noexcept {
  return ref.get_len();
}

void hpString::append(char* target, unsigned orig_len,
                      const char* substr) noexcept {
  *(target + orig_len) = '\0';
  const unsigned substrLen = len(substr);
  const unsigned newLen = orig_len + substrLen;
  char* res = hpString::alloc_new_str(target, newLen);
  res += (newLen - substrLen);
  while (*substr) *(res++) = *(substr++);
  *(res + 1) = '\0';
  target = res - newLen;
}

void hpString::append(hpString& ref, const char* substr) {
  const unsigned substrLen = len(substr);
  const unsigned newLen = ref.length + substrLen;
  char* res = hpString::alloc_new_str(ref.str_body, newLen);
  res += (newLen - substrLen);
  while (*substr) *(res++) = *(substr++);
  *(res + 1) = '\0';
  res -= newLen;
  ref.reserve(newLen);
  ref.set_str(res);
}

void hpString::append(hpString& ref, char c) {
  const unsigned newLen = ref.length + 1;
  char* res = hpString::alloc_new_str(ref.str_body, newLen);
  res += (newLen - 1);
  *res = c;
  *(res + 1) = '\0';
  res -= 1;
  ref.reserve(newLen);
  ref.set_str(res);
}

void hpString::append(hpString& ref, const hpString& subref) {
  const unsigned newLen = ref.get_len() + subref.get_len();
  const char* substr = subref.get_c_str();
  char* res = hpString::alloc_new_str(ref.get_c_str(), newLen);
  res += (ref.get_len());
  while (*substr) *(res++) = *(substr++);
  *(res + 1) = '\0';
  res -= newLen;
  ref.reserve(newLen);
  ref.set_str(res);
}

bool hpString::equal(const char* str1, const char* str2) noexcept {
  bool is_equal = false;

  // early return.
  // If their address is same.
  if (&str1 == &str2) {

    // no need to advance more.
    return true;
  }

  // if one of them is nullptr
  if (!str1 || !str2) {
    return false;
  }

  while (true) {
    if (!*str1 && !*str2) {
      is_equal = true;
      break;
    }

    if (!*str1 || !*str2) {
      is_equal = false;
      break;
    }

    if (*str1 == *str2) {
      is_equal = true;
    }
    else {
      is_equal = false;
    }
    ++str1;
    ++str2;
  }
  return is_equal;
}

bool hpString::equal(const hpString& str1, const hpString& str2) {
  if (str1 == str2) return true;
  return hpString::equal(str1.str_body, str2.str_body);
}

bool hpString::contain(const char* str, const char* substr) {
  if (str == nullptr || substr == nullptr) {
    return false;
  }
  const unsigned substrLen = len(substr);
  unsigned lencount = 0u;
  while (*str && *substr) {
    if (*str == *substr) {
      ++lencount;
      if (lencount == substrLen) return true;
    }
    ++str;
    ++substr;
  }
  return false;
}

bool hpString::contain(const char* str, char c) noexcept {
  if (str == nullptr) {
    return false;
  }

  while (*str) {
    if (*str == c) return true;
    ++str;
  }
  return false;
}

bool hpString::contain(const hpString& str, const hpString& substr) {
  if (str.empty() || substr.empty()) {
    return false;
  }

  const unsigned substrLen = substr.get_len();
  unsigned lencount = 0u;
  const char* _str = str.get_c_str();
  const char* _substr = substr.get_c_str();

  while (!*_str && !*_substr) {
    if (*_str == *_substr) {
      ++lencount;
      if (lencount == substrLen) return true;
    }
    ++_str;
    ++_substr;
  }
  return false;
}

bool hpString::contain(const hpString& str, const char* substr) {
  if (str.empty() || substr == nullptr) return false;

  const unsigned substrLen = len(substr);
  unsigned lencount = 0u;
  const char* _str = str.get_c_str();
  while (!*_str && !*substr) {
    if (*_str == *substr) {
      ++lencount;
      if (lencount == substrLen) return true;
    }
    ++_str;
    ++substr;
  }
  return false;
}

const char* hpString::copy(char* dest, const char* src) {
  if (dest == nullptr) return nullptr;
  while (*src) {
    *(dest++) = *(src++);
  }
  *(dest + 1) = '\0';
  return dest;
}

const char* hpString::copy(const char* str1, const char* str2) {
  if (str1 == nullptr) return nullptr;
  const unsigned newLen = hpString::len(str2);
  char* res = hpString::alloc_new_str(str1, newLen);
  while (*str2 != '\0') *(res++) = *(str2++);
  *(res + 1) = '\0';
  return res;
}

const char* hpString::concat(char* dest, const char* src) {
  if (dest == nullptr) return nullptr;
  const unsigned destLen = hpString::len(dest);
  const unsigned newLen = destLen + hpString::len(src);
  char* res = hpString::alloc_new_str(dest, newLen);
  res += destLen;
  while (*src != '\0') *res++ = *src++;
  *(res + 1) = '\0';
  res -= newLen;
  dest = res;
  return res;
}

const char* hpString::concat(const char* str1, const char* str2) {
  if (str1 == nullptr) return nullptr;
  const unsigned destLen = hpString::len(str1);
  const unsigned newLen = destLen + hpString::len(str2);
  char* res = hpString::alloc_new_str(str1, newLen);
  res += destLen;
  while (*str2 != '\0') *(res++) = *(str2++);
  *(res + 1) = '\0';
  return res - newLen;
}

hpString hpString::make_new() noexcept { return hpString{}; }

hpString hpString::make_new(const char* str) noexcept { return hpString{ str }; }

hpString hpString::make_new(const char* str, unsigned capacity) noexcept {
  return hpString{ str, capacity };
}

bool hpString::operator<(const hpString& ref) const noexcept {
  return str_body < ref.str_body;
}

bool hpString::operator>(const hpString& ref) const noexcept {
  return str_body > ref.str_body;
}

bool hpString::operator==(const hpString& comp) const noexcept {
  return (equal(str_body, comp.str_body) && length == comp.length);
}

void hpString::operator<<(const hpString& add) noexcept {
  hpString::append(str_body, hpString::len(str_body), add.str_body);
}

void hpString::operator<<(const char* add) noexcept {
  hpString::append(str_body, hpString::len(str_body), add);
}

void hpString::operator<<(char add) noexcept {
  hpString::append(str_body, hpString::len(str_body), &add);
}

char hpString::operator[](int index) noexcept {

  // TRACE_ERROR_EXPR("Index cannot be over total size of string!", [=]() {
  // return SCAST(unsigned, index) > mLength; });
  return str_body[index];
}

size_t hpString::operator()(const hpString& cpy) noexcept {
  return (std::hash<unsigned>::_Do_hash(cpy.get_len() << 1) >> 1) * 32 ^
    (std::hash<unsigned>::_Do_hash(cpy.get_cap() << 1)) * 33;
}

bool hpString::empty() const noexcept { return (!str_body || len(str_body) == 0); }

const char* hpString::reverse() {

  // TRACE_ERROR_EXPR("This string is not assigned yet!", [=]() { return
  // mCapacity <= 0 || mLength <= 0; });
  const unsigned orig_size = hpString::len(str_body);
  char* result_str = hpString::alloc_new_str(orig_size);
  unsigned pusher = 0u;
  while (*(str_body++)) ++pusher;
  char* last_char = str_body;
  for (unsigned i = orig_size + 1; i > 0; i--) {
    *(++result_str) = *(--last_char);
  }
  str_body = str_body - pusher - 1;
  result_str = (result_str - orig_size + 1);
  result_str = hpString::alloc_new_str(result_str);
  return result_str;
}

int hpString::reserve(unsigned new_size) {
  if (capacity > new_size) {
    return -1;
  }

  const char* temp_str = std::move(str_body);
  str_body = hpString::alloc_new_str(new_size);
  while (*(temp_str) != '\0') *(str_body++) = *(temp_str++);

  capacity = new_size;
  length = new_size;
  return 0;
}

void hpString::reset(const char* str) {
  str_body = new char[len(str)];
  *(str_body + 1) = '\0';
  while (*str) *(++str_body) = *(str++);
  *str_body = '\0';
}

bool hpString::equal(const char* str) { return hpString::equal(str_body, str); }

bool hpString::eqaul(const hpString& str) {
  return hpString::equal(*this, str);
}

hpString& hpString::append(const hpString& ref) {
  hpString::append(*this, ref);
  return *this;
}

hpString& hpString::append(hpString&& mov) {
  hpString::append(*this, std::move(mov));
  return *this;
}

hpString& hpString::append(const char* str) {
  hpString::append(*this, str);
  return *this;
}

hpString& hpString::append(char c) {
  hpString::append(*this, c);
  return *this;
}

hpString& hpString::insert(unsigned location, hpString&& mov) {
  if (location < 0 || location > length) {
    return *this;
  }

  char* temp_str = std::move(str_body);
  char* start_from = (str_body + location);
  char* target_str = mov.str_body;
  const unsigned target_len = hpString::len(target_str);
  const unsigned new_len = length + target_len;
  if (capacity < new_len) {
    str_body = hpString::alloc_new_str(length);
    capacity = new_len;
  }

  while (*str_body) {
    if (*str_body == *start_from) {
      unsigned counter = 0u;
      if (counter++ < target_len) {
        *(str_body++) = *(target_str);
      }
    }
    *(str_body++) = *(temp_str);
  }

  do {
    delete start_from;
    start_from = nullptr;
  }
  while (start_from != nullptr);

  do {
    delete temp_str;
    temp_str = nullptr;
  }
  while (temp_str != nullptr);

  do {
    delete target_str;
    target_str = nullptr;
  }
  while (target_str != nullptr);
  return *this;
}

hpString& hpString::insert(unsigned location, const hpString& cpy) {
  if (location < 0 || location > length) {
    return *this;
  }

  char* temp_str = std::move(str_body);
  char* start_from = (str_body + location);
  char* target_str = cpy.str_body;
  const unsigned target_len = hpString::len(target_str);
  const unsigned new_len = length + target_len;
  if (capacity < new_len) {
    str_body = hpString::alloc_new_str(length);
    capacity = new_len;
  }

  while (*str_body) {
    if (*str_body == *start_from) {
      unsigned counter = 0u;
      if (counter++ < target_len) {
        *(str_body++) = *(target_str++);
      }
    }
    *(str_body++) = *(temp_str);
  }

  do {
    delete start_from;
    start_from = nullptr;
  }
  while (start_from != nullptr);

  do {
    delete temp_str;
    temp_str = nullptr;
  }
  while (temp_str != nullptr);

  do {
    delete target_str;
    target_str = nullptr;
  }
  while (target_str != nullptr);
  return *this;
}

hpString& hpString::insert(unsigned location, const char* str) {
  if (location < 0 || location > length) {
    return *this;
  }

  char* temp_str = std::move(str_body);
  char* start_from = (str_body + location);
  const unsigned target_len = hpString::len(str);
  const unsigned new_len = length + target_len;
  if (capacity < new_len) {
    str_body = hpString::alloc_new_str(length);
    capacity = new_len;
  }

  while (*str_body) {
    if (*str_body == *start_from) {
      unsigned counter = 0u;
      if (counter++ < target_len) {
        *(str_body++) = *(str++);
      }
    }
    *(str_body++) = *(temp_str++);
  }

  do {
    delete start_from;
    start_from = nullptr;
  }
  while (start_from != nullptr);

  do {
    delete temp_str;
    temp_str = nullptr;
  }
  while (temp_str != nullptr);

  return *this;
}

hpString& hpString::insert(unsigned location, char c) {
  char* temp_str = std::move(str_body);
  char* start_from = (str_body + location);
  const unsigned new_len = length + 1u;
  if (capacity < new_len) {
    while (str_body != nullptr) {
      delete str_body;
      str_body = nullptr;
    }

    str_body = new char[new_len];
    capacity = new_len;
  }

  while (*str_body) {

    // 같은 위치.
    if (*str_body == *start_from) {
      *(str_body++) = c;
    }
    *(str_body++) = *(temp_str++);
  }

  do {
    delete start_from;
    start_from = nullptr;
  }
  while (start_from != nullptr);

  do {
    delete temp_str;
    temp_str = nullptr;
  }
  while (temp_str != nullptr);

  return *this;
}

void hpString::print() const noexcept {
  for (unsigned i = 0; i < length; ++i) {
    std::cout << str_body[i];
  }
}

void hpString::println() const noexcept {
  for (unsigned i = 0; i < length; ++i) {
    std::cout << str_body[i];
  }
  std::cout << std::endl;
}

const char* hpString::get_c_str() const noexcept { return str_body; }

char* hpString::get_editable_c_str() noexcept { return str_body; }

void hpString::set_str(const char* str) { str_body = const_cast<char*>(str); }

unsigned hpString::get_len() const noexcept { return length; }

void hpString::setLength(unsigned length) { length = length; }

unsigned hpString::get_cap() const noexcept { return capacity; }

void hpString::set_cap(unsigned cap) { capacity = cap; }

char* hpString::alloc_new_str(unsigned new_size) {
  const unsigned res_size = sizeof(char) * new_size;
  char* res = new char[res_size];
  *(res + res_size) = '\0';
  return res;
}

char* hpString::alloc_new_str(const char* orig) {
  const unsigned orig_size = len(orig);
  const unsigned res_size = sizeof(char) * orig_size;
  char* res = new char[res_size];
  *(res + res_size) = '\0';
  while (*orig) *(res++) = *(orig++);
  *(res - orig_size) = '\0';
  return res;
}

char* hpString::alloc_new_str(const char* orig, unsigned new_size) {
  char* res = new char[new_size + 1];
  *(res + new_size + 1) = '\0';

  unsigned pusher = 0u;
  while (*orig) {
    *(res++) = *(orig++);
    ++pusher;
  }
  *(res + (new_size - pusher)) = '\0';
  res -= pusher;
  return res;
}
};  // namespace hp
