#include "hpDebug.h"
#include <iostream>
#include <cassert>
#include <string>

namespace hp {
void hpDebug::log(Trace_String message,
                  bool is_append_info /*= true*/) noexcept {
  std::cout << hpDebug::get_info_string(is_append_info) << message << std::endl;
}

bool
hpDebug::log(Trace_String message,
             bool expr,
             bool is_append_info /*= true*/) noexcept {
  if (!expr) {
    hpDebug::log(message, expr, is_append_info);
    return true;
  }
  else {
    return false;
  }
}

void hpDebug::err(Trace_String message,
                  bool is_append_info /*= true*/) noexcept {
  std::cerr << hpDebug::get_info_string(is_append_info) << message << std::endl;
}

bool
hpDebug::err(Trace_String message,
             bool expr,
             bool is_append_info /*= true*/) noexcept {
  if (!expr) {
    hpDebug::err(message, expr, is_append_info);
    return true;
  }
  else {
    return false;
  }
}

void hpDebug::check(std::function<bool()>&& expr, bool is_append_info /*= true*/) noexcept {
  if (expr) {
    std::cerr << hpDebug::get_info_string(is_append_info) << std::endl;
    assert(true);
  }
}

void hpDebug::check_always(bool is_append_info /*= true*/) noexcept {
  std::cerr << hpDebug::get_info_string(is_append_info) << std::endl;
  assert(true);
}

void hpDebug::check_always(Trace_String message,
                           bool is_append_info /*= true*/) noexcept {
  std::cerr << hpDebug::get_info_string(is_append_info) << message << std::endl;
  assert(true);
}

void hpDebug::check_always(Trace_String message,
                           std::function<void()>&& fin,
                           bool is_append_info /*= true*/) noexcept {
  std::cerr << hpDebug::get_info_string(is_append_info) << message << std::endl;
  fin();
  assert(true);
}

void hpDebug::check(Trace_String message,
                    bool expr,
                    bool is_append_info /*= true*/) noexcept {
  if (!expr) {
    std::cerr << hpDebug::get_info_string(is_append_info) << message << std::endl;
    assert(true);
  }
}

void hpDebug::check(bool expr,
                    std::function<void()>&& fin,
                    bool is_append_info /*= true*/) noexcept {
  if (!expr) {
    std::cerr << hpDebug::get_info_string(is_append_info) << std::endl;
    fin();
    assert(true);
  }
}

void hpDebug::check(Trace_String message,
                    bool expr,
                    std::function<void()>&& fin,
                    bool is_append_info /*= true*/) noexcept {
  if (!expr) {
    std::cerr << hpDebug::get_info_string(is_append_info) << std::endl;
    fin();
    assert(true);
  }
}

const char*
hpDebug::get_info_string(bool is_append_info /*= true*/) {
  if (is_append_info) {
    const unsigned buf_size = (sizeof(char) * 128);
    char result_buf[buf_size]{};
    sprintf_s(result_buf, buf_size,
              "%s [ %s : %l ] ",
              __FUNCTION__,
              __FILE__,
              __LINE__);
    return result_buf;
  }
  else {
    return "";
  }

}
};  // namespace hp
