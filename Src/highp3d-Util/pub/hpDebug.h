#pragma once
#include "hpMacro.h"
#include "hpString.h"

#include <functional>

namespace hp {
class hpDebug final {
  DELETE_CDTOR_COPY_MOVE(hpDebug)

private:
  static hpString print_info();

public:
  static bool log(hpString message, bool is_append_info = true, bool is_expr_true = true) noexcept;
  static bool err(hpString message, bool is_append_info = true, bool is_expr_true = true) noexcept;
  static void check(bool is_expr_true, bool is_append_info = true) noexcept;
  static void check_msg(hpString message, bool is_append_info = true, bool is_expr_true = true) noexcept;
  static void check_fin(bool is_expr_true, std::function<void()>&& fin, bool is_append_info = true) noexcept;
  static void check_msg_fin(hpString message, bool is_expr_true, std::function<void()>&& fin, bool is_append_info = true) noexcept;
};
};  // namespace hp

//#include "hpDebug.inl"
