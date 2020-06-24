#include "../pub/hpObjectHelper.h"

namespace hp {
#pragma region static fields initialisation.
bool hpObjectHelper::is_instanceID_prepared = false;

std::tuple<bool, unsigned> hpObjectHelper::instanceID_arr[rand_instaceID_amount]{};
#pragma endregion


void hpObjectHelper::prepare_rand_instanceID() noexcept {
  if (is_instanceID_prepared) {
    return;
  }

  for (unsigned i = 0; i < rand_instaceID_amount; ++i) {
    instanceID_arr[i] = hpObjectHelper::T_uniq_instanceID_tuple{ false, i };
  }

  is_instanceID_prepared = true;
}

hpObjectHelper::T_uniq_instanceID
hpObjectHelper::make_rand_instanceID() noexcept {
  for (unsigned i = 0; i < rand_instaceID_amount; ++i) {
    // if the key is already used!
    if (std::get<e_rand_instanceID_key::e_is_instanceID_used>(instanceID_arr[i])) {
      continue;
    }
    std::get<e_rand_instanceID_key::e_is_instanceID_used>(instanceID_arr[i]) = true;
    return std::get<e_rand_instanceID_key::e_uniq_instanceID>(instanceID_arr[i]);
  }
  return hpObjectHelper::err_instanceID;
}
};  // namespace hp
