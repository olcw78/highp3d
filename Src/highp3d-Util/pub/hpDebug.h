#pragma once
#include "hpMacro.h"
#include <functional>

namespace hp {
class hpDebug final {
  DELETE_CDTOR_COPY_MOVE(hpDebug)

public:
  using Trace_String = const char*;
  static void Trace(Trace_String func, Trace_String file, long line,
                    Trace_String message) noexcept;
  static bool Trace_Expr(Trace_String func, Trace_String file, long line,
                         Trace_String message,
                         std::function<bool()>&& expr) noexcept;
  static void Trace_Error(Trace_String func, Trace_String file, long line,
                          Trace_String message) noexcept;
  static bool Trace_Error_Expr(Trace_String func, Trace_String file, long line,
                               Trace_String message,
                               std::function<bool()>&& expr) noexcept;
  static void Trace_Assert(Trace_String func, Trace_String file, long line,
                           std::function<bool()>&& expr) noexcept;
  static void Trace_Assert_Always(Trace_String func, Trace_String file,
                                  long line) noexcept;
  static void Trace_Assert_Message(Trace_String func, Trace_String file,
                                   long line, Trace_String message,
                                   std::function<bool()>&& expr) noexcept;
  static void Trace_Assert_Final(Trace_String func, Trace_String file,
                                 long line, std::function<bool()>&& expr,
                                 std::function<void()>&& fin) noexcept;
  static void Trace_Assert_Message_Final(Trace_String func, Trace_String file,
                                         long line, Trace_String message,
                                         std::function<bool()>&& expr,
                                         std::function<void()>&& fin) noexcept;
};
};  // namespace hp

#include "hpDebug.inl"

#define TRACE_ASSERT_ALWAYS() \
  hp::hpDebug::Trace_Assert_Always(__FUNCTION__, __FILE__, __LINE__)

#define TRACE_ASSERT(Expr)                                            \
  hp::hpDebug::Trace_Assert(__FUNCTION__, __FILE__, __LINE__, \
                                    std::move(Expr))

#define TRACE_ASSERT_FINAL(Expr, Final)                                     \
  hp::hpDebug::Trace_Assert_Final(__FUNCTION__, __FILE__, __LINE__, \
                                          std::move(Expr), std::move(Final))

#define TRACE_ASSERT_MESSAGE_ALWAYS(Message)                                  \
  hp::hpDebug::Trace_Assert_Message(__FUNCTION__, __FILE__, __LINE__, \
                                            Message,                          \
                                            std::move([]() { return true; }))

#define TRACE_ASSERT_MESSAGE(Message, Expr)                                   \
  hp::hpDebug::Trace_Assert_Message(__FUNCTION__, __FILE__, __LINE__, \
                                            Message, std::move(Expr))

#define TRACE_ASSERT_MESSAGE_FINAL(Message, Expr, Final)          \
  hp::hpDebug::Trace_Assert_Message_Final(                \
      __FUNCTION__, __FILE__, __LINE__, Message, std::move(Expr), \
      std::move(Final))

#define TRACE_ERROR_EXPR(Message, Expr)                                   \
  hp::hpDebug::Trace_Error_Expr(__FUNCTION__, __FILE__, __LINE__, \
                                        Message, std::move(Expr))

#define TRACE_ERROR(Message) \
  hp::hpDebug::Trace_Error(__FUNCTION__, __FILE__, __LINE__, Message)

#define TRACE_EXPR(Message, Expr)                                            \
  hp::hpDebug::Trace_Expr(__FUNCTION__, __FILE__, __LINE__, Message, \
                                  std::move(Expr))

#define TRACE(Message) \
  hp::hpDebug::Trace(__FUNCTION__, __FILE__, __LINE__, Message)

#define TRACE_LOG() \
  hp::hpDebug::Trace(__FUNCTION__, __FILE__, __LINE__, "")
