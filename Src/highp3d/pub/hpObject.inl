#include "hpObject.h"

namespace hp {
template <typename CompT, typename>
CompT
hpObject::Instantiate(CompT&& obj) {
  return CompT{ std::forward<CompT>(obj) };
}

//template <typename CompT, typename>
//inline CompT Object::Instantiate(CompT&& obj, glm::vec3 pos, glm::quat rot) {
//	return CompT{std::forward<CompT>(obj), pos, rot};
//}
//
//template <typename CompT, typename... Comps, typename, typename>
//inline CompT Object::Instantiate(Comps&&... obj, glm::vec3 pos, glm::quat rot) {
//
//}

//template <typename CompT, typename>
//inline CompT Object::FindObjectOfType(CompT type) {
//
//}
//
//template <typename CompT, typename>
//inline std::vector<NoDeletePtr(std::add_pointer_t<CompT>)>
//Object::FindObjectsOfType(CompT type) {
//
//}
}; // namespace hp
