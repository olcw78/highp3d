#include "../pub/hpCallbacks.h"

namespace hp {
namespace opengl {
bool hpCallbacks::is_first_mouse_input = true;
float hpCallbacks::last_x = 0.0f;
float hpCallbacks::last_y = 0.0f;

//HP_InputComponent Callbacks::SystemInput;

void hpCallbacks::Callback_On_Frame_Buffer_Resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void hpCallbacks::Callback_On_Mouse_Receive(GLFWwindow* window, double x, double y) {
	if (is_first_mouse_input) {
		last_x = (float)x;
		last_y = (float)y;
		is_first_mouse_input = false;
	}

	float x_offset = (float)x - last_x;
	float y_offset = last_y - (float)y;
	last_x = (float)x;
	last_y = (float)y;
}

void hpCallbacks::Callback_On_Mouse_Scroll_Receive(GLFWwindow* window, double x, double y) {}

void hpCallbacks::Callback_On_Error_Receive(int errorCode, char const* description) {
	char buf[128];
	sprintf_s(buf, sizeof(buf), "GLFW Error %d: %s\n", errorCode, description);	
	hpDebug::err(buf);
}

void hpCallbacks::Callback_On_Keyboard_Receive(GLFWwindow* window, int key, int scan_code, int action, int modes) {
	/*if (HP_InputComponent::GetKeyDown(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}*/

	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
};
};
