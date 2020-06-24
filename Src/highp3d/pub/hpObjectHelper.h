#pragma once

#pragma once


#include "hpRandom.h"
#include "hpObject.h"

namespace hp {
class hpObjectHelper final {
  DELETE_CDTOR_COPY_MOVE(hpObjectHelper)

public:  
  friend class hpObject;

  static unsigned make_rand_instanceID() noexcept;

public:
  constexpr static unsigned instanceID_amount = 5012u;

private:
  static bool is_rand_instanceID_created;
  static std::tuple<bool, unsigned> rand_instanceIDs_arr[instanceID_amount];
};
};  // namespace hp
