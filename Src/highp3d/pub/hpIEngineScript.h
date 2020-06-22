#pragma once
#pragma once

namespace hp {
class hpIEngineScript {
public:
  hpIEngineScript() = default;
  ~hpIEngineScript() = default;

public:
  virtual void on_start() = 0;
  virtual void on_update() = 0;
  virtual void on_late_update() = 0;
  virtual void on_destroy() = 0;
};
}; // namespace hp
