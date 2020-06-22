#pragma once

//#include "Shared.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
//#include "hpMacro.h"
#include "hpMacro.h"
#include "hpDebug.h"

#include "hpIEngineScript.h"
#include "hpEngineScriptHolder.h"
#include "hpCallbacks.h"

//#include "EngineScriptSets.h"
//#include "IEngineScript.h"
//#include "Callbacks.h"

namespace hp { 
namespace opengl {


constexpr int RETURN_SUCCESS = 0;
constexpr int RETURN_FAILED = 1;

/// <summary>
/// 
/// </summary>
class hpOpenglCore final {
public:
  explicit hpOpenglCore() noexcept;
  explicit hpOpenglCore(hpEngineScriptHolder* new_engine_scripts_holder) noexcept;
  ~hpOpenglCore() noexcept;

public:
  int init(int new_width, int new_height, const char* new_wnd_name);
  void dispose();
  void start();
  void update();

private:
  void init_gl_states();
  void init_resources();

public:
  GLFWwindow* get_wnd() noexcept;  
  int get_width() const noexcept;  
  int get_height() const noexcept;  
  void attach_engine_scripts_holder(hpIEngineScript* src);

  /*template <typename... Args,
    typename = std::enable_if_t<std::is_convertible_v<std::decay_t<Args>..., class IEngineScript>>>
    void AttachEngineScripts(Args&&... srcs);*/

  hpEngineScriptHolder* get_engine_scripts_holder() noexcept;

private:
  GLFWwindow* window;
  int width;
  int height;
  std::unique_ptr<hpEngineScriptHolder> engine_scripts_holder;
};
}; // opengl
}; // hp

//#include "Core.inl"