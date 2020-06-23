#include "../pub/hpOpenglCore.h"
#include <iostream>

namespace hp {
namespace opengl {
hpOpenglCore::hpOpenglCore() noexcept {
  //
  window = nullptr;
  width = 0;
  height = 0;
  engine_scripts_holder = std::make_unique<hpEngineScriptHolder>();
}

hpOpenglCore::hpOpenglCore(hpEngineScriptHolder* new_script_holder) noexcept {
  window = nullptr;
  width = 0;
  height = 0;
  engine_scripts_holder = std::make_unique<hpEngineScriptHolder>(*new_script_holder);
}

hpOpenglCore::~hpOpenglCore() noexcept {
  SDEL2(window);
}

int
hpOpenglCore::init(int width, int height, const char* windowName) {
  glfwSetErrorCallback(hpCallbacks::Callback_On_Error_Receive);
  if (!glfwInit()) {
    return RETURN_FAILED;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
  width = width;
  height = height;

  if (window == nullptr) {
    hpDebug::err("Failed to create GLFW windows!");    
    return RETURN_FAILED;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, hpCallbacks::Callback_On_Frame_Buffer_Resize);
  glfwSetCursorPosCallback(window, hpCallbacks::Callback_On_Mouse_Receive);
  glfwSetScrollCallback(window, hpCallbacks::Callback_On_Mouse_Scroll_Receive);
  glfwSetKeyCallback(window, hpCallbacks::Callback_On_Keyboard_Receive);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    hpDebug::err("Failed to intialise the OpenGL loader (GLAD).");
    return RETURN_FAILED;
  }

  init_gl_states();
  init_resources();

  return RETURN_SUCCESS;
}

void hpOpenglCore::dispose() {
  engine_scripts_holder->on_destroy();
}

void hpOpenglCore::start() {
  engine_scripts_holder->on_start();  
}

void hpOpenglCore::update() {  
  hpDebug::err("Window is invalid!", get_wnd() != nullptr, true);
  while (!glfwWindowShouldClose(get_wnd())) {
    glfwSwapBuffers(get_wnd());
    glfwPollEvents();

    engine_scripts_holder->on_update();
    engine_scripts_holder->on_late_update();

    std::cout << "Core is updating now!" << std::endl;
  }
}

void hpOpenglCore::init_gl_states() {}

void hpOpenglCore::init_resources() {}

GLFWwindow* hpOpenglCore::get_wnd() noexcept { return window; }

int
hpOpenglCore::get_width() const noexcept { return width; }

int
hpOpenglCore::get_height() const noexcept { return height; }

hpEngineScriptHolder*
hpOpenglCore::get_engine_scripts_holder() noexcept {
  return engine_scripts_holder.get();
}

void hpOpenglCore::attach_engine_scripts_holder(hpIEngineScript* new_engine_script) {
  engine_scripts_holder->attach_to_scripts_holder(new_engine_script);
}

};  // namespace opengl
};  // namespace hp
