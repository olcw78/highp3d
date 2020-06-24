#include "../pub/hpObject.h"
#include "../pub/hpObjectHelper.h"

namespace hp {
hpObject::hpObject() noexcept {
  mInstanceId = hpObjectHelper::make_rand_instanceID();
  mName = hpString{ "hpObject" + mInstanceId };
}

hpObject::hpObject(hpString&& str) noexcept {
  mInstanceId = hpObjectHelper::make_rand_instanceID();
  mName = std::forward<hpString>(str);
  //
}

std::ostream&
operator<<(std::ostream& ostr, const hpObject& obj) noexcept {
  char* str = new char[64];
  *str = '\0';
  sprintf_s(str, sizeof(str), " [ Name: %s, InstanceID: %zu",
            obj.mName.get_c_str(), obj.mInstanceId);
  while (*str) {
    ostr << *(str++);
  }
  return ostr;
}

bool 
hpObject::operator==(const hpObject& ref) noexcept {
  return (mInstanceId == ref.mInstanceId && mName.eqaul(ref.mName));
}

bool 
hpObject::destroy_self(float delay) {
  return false;
}

bool
hpObject::Destroy(const hpObject& ref, float delay) {
  return false;
}

hpString 
hpObject::ToStr() const noexcept { return mName; }

unsigned
hpObject::getInstanceId() const noexcept { return mInstanceId; }

hpString
hpObject::getName() const noexcept { return mName; }

void hpObject::setName(hpString&& name) { mName = std::move(name); }
};  // namespace hp
