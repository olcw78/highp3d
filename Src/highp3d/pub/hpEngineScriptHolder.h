#pragma once
#include <list>

#include "hpIEngineScript.h"

namespace hp {
class hpEngineScriptHolder final {
public:
  hpEngineScriptHolder() noexcept;
  ~hpEngineScriptHolder() noexcept;

public:
  void on_start();
  void on_update();
  void on_late_update();
  void on_destroy();

public:
  void attach_to_scripts_holder(hpIEngineScript* new_engine_script);
  std::list<hpIEngineScript*>& get_scripts_refs() noexcept;

private:
  std::list<hpIEngineScript*> scripts_holder_list;
};
};  // namespace hp
