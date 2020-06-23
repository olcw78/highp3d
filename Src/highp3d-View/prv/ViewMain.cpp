
#include <iostream>

#include "hpOpenglCore.h"
#include "View.h"

namespace {
constexpr unsigned WINDOW_WIDTH = 1920u;
constexpr unsigned WINDOW_HEIGHT = 1080u;
constexpr const char* WINDOW_NAME = "highp3d - 01. render the basic triangle";
}; 

int main(int argc, char** argv) {
  static hp::opengl::hpOpenglCore core;
  if (core.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME) == hp::opengl::RETURN_FAILED) {
    std::cout << "Init Opengl-Core failed!" << std::endl;
    return hp::opengl::RETURN_FAILED;
  }

  static hp::View view;
  core.attach_engine_scripts_holder(&view);

  core.start();
  core.update();
  core.dispose();

  return hp::opengl::RETURN_SUCCESS;
}