#pragma once

#include <tuple>
#include <map>

#include "hpRandom.h"

//#include "hpObject.h"

namespace hp {
class hpObjectHelper final {

  DELETE_CDTOR_COPY_MOVE(hpObjectHelper)

public:
  friend class hpObject;

private:
  using T_is_instanceID_used = bool;
  using T_uniq_instanceID = unsigned;
  using T_uniq_instanceID_tuple = std::tuple<T_is_instanceID_used, T_uniq_instanceID>;


public:
  static const T_uniq_instanceID err_instanceID = 99999u;
  /// <summary>
  /// use only this as a key for <T_instanceID_tuple> (std::get<0>...>
  /// </summary>
  enum e_rand_instanceID_key : unsigned {
    e_is_instanceID_used = 0,
    e_uniq_instanceID = 1,
  };

public:
  static void prepare_rand_instanceID() noexcept;
  /// <summary>
  /// get an unique instanceID.
  /// </summary>
  /// <returns></returns>
  static T_uniq_instanceID make_rand_instanceID() noexcept;  

public:
  constexpr static unsigned rand_instaceID_amount = 5012u;

private:
  static bool is_instanceID_prepared;
  static T_uniq_instanceID_tuple instanceID_arr[rand_instaceID_amount];  
};
};  // namespace hp
