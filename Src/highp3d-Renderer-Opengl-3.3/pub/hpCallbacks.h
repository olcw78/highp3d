#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "hpMacro.h"
#include "hpDebug.h"

//#include "InputComponent.h"

namespace hp {
namespace opengl {
/// <summary>
/// static class.
/// </summary>
class hpCallbacks final {
  DELETE_CDTOR_COPY_MOVE(hpCallbacks)

public:
  static void Callback_On_Frame_Buffer_Resize(GLFWwindow* window, int width, int height);
  static void Callback_On_Mouse_Receive(GLFWwindow* window, double x, double y);
  static void Callback_On_Mouse_Scroll_Receive(GLFWwindow* window, double x, double y);
  static void Callback_On_Error_Receive(int errorCode, char const* description);
  static void Callback_On_Keyboard_Receive(GLFWwindow* window, int key, int scan_code, int action, int modes);

private:
  static bool is_first_mouse_input;
  static float last_x;
  static float last_y;

  //static HP_InputComponent SystemInput;
};
}; // opengl
}; // hp
#pragma once
