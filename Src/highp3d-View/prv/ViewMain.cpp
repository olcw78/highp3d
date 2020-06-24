
#include <iostream>

#include "hpOpenglCore.h"
#include "View.h"
#include "hpString.h"
#include "hpDebug.h"

namespace {
constexpr unsigned WINDOW_WIDTH = 1920u;
constexpr unsigned WINDOW_HEIGHT = 1080u;
constexpr const char* WINDOW_NAME = "highp3d - 01. render the basic triangle";
};

/// <summary>
/// Entry point of highp3d-View.
/// </summary>
/// <returns></returns>
int main() {
  static hp::opengl::hpOpenglCore core;
  hp::hpDebug::check_msg("Init Opengl-Core(glfw | 3.3) failed!", true,
                         core.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME) == hp::opengl::RETURN_SUCCESS);

  static hp::View view;
  core.attach_engine_scripts_holder(&view);

  core.start();
  core.update();
  core.dispose();

  return hp::opengl::RETURN_SUCCESS;
}