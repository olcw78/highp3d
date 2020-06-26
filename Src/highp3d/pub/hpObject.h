#pragma once

#include "hpDebug.h"
#include "hpMacro.h"
#include "hpString.h"

//#include "ReturnValueWrapper.h"

namespace hp {
/// <summary>
/// the basic object of the hpGameObject or hpComponent.
/// </summary>
class hpObject {
public:
  friend std::ostream& operator<<(std::ostream& ostr, hpObject const& obj);
  friend std::istream& operator>>(std::istream&, const hpObject&) = delete;

public:
  friend class hpObjectHelper;
  hpObject() noexcept;

  //Object(glm::vec3 pos = glm::vec3{0.0f}, glm::quat rot = glm::quat{0.0f}) noexcept;
  hpObject(hpString&& str) noexcept;
  /*template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, Object>>>
  Object(CompT&& obj) noexcept;*/

  virtual ~hpObject() noexcept = default;

  MAKE_COPY_MOVE_DEFAULT(hpObject)

    bool operator==(const hpObject& ref) noexcept;

public:
  template <typename CompT,
    typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, hpObject>>>
    static CompT instantiate(CompT&& obj);

  /*template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, Object>>>
  static CompT Instantiate(CompT&& obj, glm::vec3 pos = glm::vec3{0.0f}, glm::quat rot = glm::quat{0.0f});
*/
/*template <typename CompT,
  typename... Comps,
  typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, Object>>,
  typename = std::enable_if_t<std::is_convertible_v<std::decay_t<Comps>..., Object>>>
  static CompT Instantiate(Comps&&... obj, glm::vec3 pos = glm::quat{0.0f}, glm::quat rot = glm::quat{0.0f});*/

  /*template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, Object>>>
  static CompT FindObjectOfType(CompT type);

  template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, Object>>>
  static std::vector<NoDeletePtr(std::add_pointer_t<CompT>)>
  FindObjectsOfType(CompT type);*/

  virtual bool destroy_self(float delay = 0.0f);
  static bool destroy(const hpObject& ref, float delay = 0.0f);

  virtual hpString to_str() const noexcept;

public:
  unsigned get_instanceID() const noexcept;
  hpString get_name() const;
  void set_name(hpString&& name);

protected:
  unsigned instanceID;
  hpString name;
};
};  // namespace hp

std::ostream& operator<<(std::ostream& ostr, hp::hpObject const& str);


#include "hpObject.inl"
