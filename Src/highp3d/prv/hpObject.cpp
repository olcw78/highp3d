#include "../pub/hpObject.h"

namespace hp {
hpObject::hpObject() noexcept {
  instanceID = hpObjectHelper::make_rand_instanceID();
  name = hpString{ "Object" + instanceID };
}

//Object::Object(glm::vec3 pos, glm::quat rot) noexcept {
//
//}

hpObject::hpObject(hpString&& str) noexcept {
  instanceID = hpObjectHelper::make_rand_instanceID();
  name = std::forward<hpString>(str);
  //
}

bool
hpObject::operator==(const hpObject& ref) noexcept {
  return (instanceID == ref.instanceID && hpString::equal(name, ref.name));
}

bool
hpObject::destroy_self(float delay) {
  return false;
}

bool
hpObject::destroy(const hpObject& ref, float delay) {
  return false;
}

hpString
hpObject::to_str() const noexcept { return name; }

unsigned
hpObject::get_instanceID() const noexcept { return instanceID; }

hpString
hpObject::get_name() const { return name; }

void hpObject::set_name(hpString&& name) { name = std::forward<hpString>(name); }

};  // namespace hp

std::ostream&
operator<<(std::ostream& ostr, hp::hpObject const& obj) noexcept {
  constexpr unsigned len_str = (sizeof(char) * 64);
  char str[len_str]{ };
  sprintf_s(str, len_str,
            " [ Name: %s, InstanceID: %zu ] ",
            obj.get_name().get_c_str(),
            obj.get_instanceID());
  ostr << str;
  return ostr;
}
