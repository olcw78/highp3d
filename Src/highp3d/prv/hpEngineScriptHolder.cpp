#include "../pub/hpEngineScriptHolder.h"

namespace hp {
hpEngineScriptHolder::hpEngineScriptHolder() noexcept
  : scripts_holder_list{} {
  //
}

hpEngineScriptHolder::~hpEngineScriptHolder() noexcept {
  for (auto& e : scripts_holder_list) {
    while (e != nullptr) {
      delete e;
      e = nullptr;
    }
  }
  scripts_holder_list.clear();
}

void hpEngineScriptHolder::on_start() {
  for (auto const& e : scripts_holder_list) {
    e->on_start();
  }
}

void hpEngineScriptHolder::on_update() {
  for (auto const& e : scripts_holder_list) {
    e->on_update();
  }
}

void hpEngineScriptHolder::on_late_update() {
  for (auto const& e : scripts_holder_list) {
    e->on_late_update();
  }
}

void hpEngineScriptHolder::on_destroy() {
  for (auto const& e : scripts_holder_list) {
    e->on_destroy();
  }
}
void hpEngineScriptHolder::attach_to_scripts_holder(hpIEngineScript* scripts) {
  scripts_holder_list.push_back(scripts);
}

std::list<hpIEngineScript*>&
hpEngineScriptHolder::get_scripts_refs() noexcept {
  return scripts_holder_list;
}
};  // namespace hp
