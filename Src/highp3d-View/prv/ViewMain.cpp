
#include <iostream>

#include "hpOpenglCore.h"
#include "View.h"

namespace {
constexpr int RETURN_FAILED = 1;
constexpr int RETURN_SUCCESS = 0;

constexpr unsigned WINDOW_WIDTH = 1920u;
constexpr unsigned WINDOW_HEIGHT = 1080u;
constexpr const char* WINDOW_NAME = "highp3d - 01. render the basic triangle";
};

int main() {

  static hp::opengl::hpOpenglCore core;
  if (RETURN_FAILED == core.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME)) {
    std::cout << "Init Opengl-Core failed!" << std::endl;
    return RETURN_FAILED;
  }

  static hp::View view;
  core.attach_engine_scripts_holder(&view);

  core.start();
  core.update();
  core.dispose();

  return RETURN_SUCCESS;
}