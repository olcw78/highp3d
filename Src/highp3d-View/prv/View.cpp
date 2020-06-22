#include "../pub/View.h"

namespace hp {
View::View() noexcept : hpIEngineScript()/*, IObservable()*/ {
  //
}

View::~View() noexcept {
  this->on_destroy();
}

void View::on_start() {
  /*hpString cube_name{ "Cube" };
  mCube = std::make_unique<GameObject>(
    cube_name,
    eComponentFlags::TRANSFORM | eComponentFlags::RENDERER | eComponentFlags::INPUT | eComponentFlags::PHYSICS);

  hpString sphere_name{ "Sphere" };
  mSphere = std::make_unique<GameObject>();
  mScene->AddChild(cube_name, mCube.get());*/
}

void View::on_update() {}

void View::on_late_update() {}

void View::on_destroy() {
  /*while (mCube != nullptr) {
    mCube->DestroyThis(0.0f);
  }*/
}

//void View::on_invoked(eEventMessage msg, void* data) {
//  switch (msg) {
//    case hp::eEventMessage::NONE:
//    break;
//
//    default:
//    break;
//  }
//}
};  // namespace hp
