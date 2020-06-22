#pragma once

#include "hpMacro.h"
#include "hpIEngineScript.h"

#include <memory>

namespace hp {
class View final : public virtual hpIEngineScript {
public:
  View() noexcept;
  ~View() noexcept;


public:
  virtual void on_start() override;
  virtual void on_update() override;
  virtual void on_late_update() override;
  virtual void on_destroy() override;
  //virtual void on_invoked(eEventMessage msg, void* data) override;

private:
  /*std::unique_ptr<GameObject> go_cube;
  std::unique_ptr<GameObject> go_cube;*/
  //std::unique_ptr<Scene> mScene;
};
}; // namespace hp