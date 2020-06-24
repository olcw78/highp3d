#include "hpDebug.h"

#include <iostream>
#include <cassert>
#include <string>

namespace hp {
bool
hpDebug::log(hpString message,
             bool is_append_info /*= true*/,
             bool is_expr_true /*= true*/) noexcept {
  if (!is_expr_true) {
    hpString result_str = print_info();
    result_str << message;
    result_str.println();
    return true;
  }
  else {
    return false;
  }
}

bool
hpDebug::err(hpString message,
             bool is_append_info /*= true*/,
             bool is_expr_true /*= true*/) noexcept {
  if (!is_expr_true) {
    hpString result_str = print_info();
    result_str << message;
    result_str.println_err();
    return true;
  }
  else {
    return false;
  }
}

void hpDebug::check(bool is_expr_true,
                    bool is_append_info/* = true*/) noexcept {
  if (is_expr_true) {
    if (is_append_info) {
      print_info().println_err();
    }
    assert(true);
  }
}

void hpDebug::check_msg(hpString message,
                        bool is_append_info /*= true*/,
                        bool is_expr_true /*= true*/) noexcept {
  if (is_expr_true) {
    if (is_append_info) {
      print_info().println_err();
    }
    assert(true);
  }
}

void hpDebug::check_fin(bool is_expr_true,
                        std::function<void()>&& fin,
                        bool is_append_info /* = true*/) noexcept {
  if (is_expr_true) {
    if (is_append_info) {
      print_info().println_err();
    }
    fin();
    assert(true);
  }
}

void hpDebug::check_msg_fin(hpString message,
                            bool is_expr_true,
                            std::function<void()>&& fin,
                            bool is_append_info /*= true*/) noexcept {
  if (is_expr_true) {
    hpString result_str = (is_append_info ? print_info() : hpString{});
    result_str << message;
    result_str.println_err();

    fin();
    assert(true);
  }
}

hpString
hpDebug::print_info() {
  constexpr unsigned size_result_buf = (sizeof(char) * 128);
  char result_buf[size_result_buf];
  sprintf_s(result_buf, size_result_buf,
            "%s [ %s : %l ] ",
            __FUNCTION__,
            __FILE__,
            __LINE__);
  return hpString{ result_buf };
}

};  // namespace hp
