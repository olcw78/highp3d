#pragma once
#include "hpMacro.h"
#include <functional>

namespace hp {
class hpDebug final {
  DELETE_CDTOR_COPY_MOVE(hpDebug)

public:
  using Trace_String = const char*;

  static void log(Trace_String message,
                  bool is_append_info = true) noexcept;

  static bool log(Trace_String message,
                  bool expr,
                  bool is_append_info = true) noexcept;

  static void err(Trace_String message, bool is_append_info = true) noexcept;

  static bool err(Trace_String message,
                  bool expr,
                  bool is_append_info = true) noexcept;

  static void check(std::function<bool()>&& expr,
                    bool is_append_info = true) noexcept;

  static void check(Trace_String message,
                    bool expr,
                    bool is_append_info = true) noexcept;

  static void check(bool expr,
                    std::function<void()>&& fin,
                    bool is_append_info = true) noexcept;

  static void check(Trace_String message,
                    bool expr,
                    std::function<void()>&& fin,
                    bool is_append_info = true) noexcept;

  static void check_always(bool is_append_info = true) noexcept;

  static void check_always(Trace_String message,
                           bool is_append_info = true) noexcept;

  static void check_always(Trace_String message,
                           std::function<void()>&& fin,
                           bool is_append_info = true) noexcept;

private:
  static const char* get_info_string(bool is_append_info = true);
};
};  // namespace hp

//#include "hpDebug.inl"
