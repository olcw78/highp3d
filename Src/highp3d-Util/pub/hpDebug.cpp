#include "hpDebug.h"
#include <iostream>
#include <cassert>

namespace hp {
void hpDebug::Trace(Trace_String func, Trace_String file, long line,
                  Trace_String message) noexcept {
  std::cout << func << ' [' << file << ' : ' << line << '] ' << message
    << std::endl;
}

bool hpDebug::Trace_Expr(Trace_String func, Trace_String file, long line,
                       Trace_String message,
                       std::function<bool()>&& expr) noexcept {
  if (!expr) {
    hpDebug::Trace(func, file, line, message);
    return true;
  }
  else {
    return false;
  }
}

void hpDebug::Trace_Error(Trace_String func, Trace_String file, long line,
                        Trace_String message) noexcept {
  std::cerr << func << ' [' << file << ' : ' << line << '] ' << message
    << std::endl;
}

bool hpDebug::Trace_Error_Expr(Trace_String func, Trace_String file,
                             long line, Trace_String message,
                             std::function<bool()>&& expr) noexcept {
  if (!expr) {
    hpDebug::Trace_Error(func, file, line, message);
    return true;
  }
  else {
    return false;
  }
}

void hpDebug::Trace_Assert(Trace_String func, Trace_String file, long line,
                         std::function<bool()>&& expr) noexcept {
  if (expr) {
    std::cerr << func << ' [' << file << ' : ' << line << '] ' << std::endl;
    assert(true);
  }
}

void hpDebug::Trace_Assert_Message(Trace_String func, Trace_String file,
                                 long line, Trace_String message,
                                 std::function<bool()>&& expr) noexcept {
  if (!expr) {
    std::cerr << func << ' [' << file << ' : ' << line << '] ' << message
      << std::endl;
    assert(true);
  }
}

void hpDebug::Trace_Assert_Final(Trace_String func, Trace_String file,
                               long line, std::function<bool()>&& expr,
                               std::function<void()>&& fin) noexcept {
  if (!expr) {
    std::cerr << func << ' [' << file << ' : ' << line << '] ' << std::endl;
    fin();
    assert(true);
  }
}

void hpDebug::Trace_Assert_Message_Final(
  Trace_String func, Trace_String file, long line, Trace_String message,
  std::function<bool()>&& expr, std::function<void()>&& fin) noexcept {
  if (!expr) {
    std::cerr << func << ' [' << file << ' : ' << line << '] ' << std::endl;
    fin();
    assert(true);
  }
}

void hpDebug::Trace_Assert_Always(Trace_String func, Trace_String file,
                                long line) noexcept {
  std::cerr << func << " [" << file << " : " << line << "] " << std::endl;
  assert(true);
}
};  // namespace hp
