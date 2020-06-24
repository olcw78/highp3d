#include "../pub/hpObjectHelper.h"

namespace hp {
bool hpObjectHelper::is_rand_instanceID_created = false;
std::tuple<bool, unsigned>
hpObjectHelper::rand_instanceIDs_arr[instanceID_amount]{};

unsigned hpObjectHelper::make_rand_instanceID() noexcept {
  if (!is_rand_instanceID_created) {
    for (unsigned i = 0; i < instanceID_amount; ++i) {
      rand_instanceIDs_arr[i] = std::tuple<bool, unsigned>{ false, i };
    }
    is_rand_instanceID_created = true;
  }

  unsigned resultId = hpRandom::rand_range_unsigned(0u, instanceID_amount);
  while (is_rand_instanceID_created) {
    for (unsigned i = 0; i < instanceID_amount; ++i) {
      if (!std::get<0>(rand_instanceIDs_arr[i])) {
        if (resultId != std::get<1>(rand_instanceIDs_arr[i])) {
          return resultId;
        }
      }
      resultId = hpRandom::rand_range_unsigned(0u, instanceID_amount);
    }
  }
}
};  // namespace hp
