#pragma once

#pragma once

#include "hpObject.h"
#include "hpString.h"

#include "hpDebug.h"
#include "hpASCII.h"
#include "hpMacro.h"

//#include "CameraComponent.h"
//#include "InputComponent.h"
//#include "PhysicsComponent.h"
//#include "RendererComponent.h"
//#include "TransformComponent.h"

namespace hp {
class GameObject
  : public hpObject {
public:
  //friend class HP_GameObjectHelper;
  using hpObject::hpObject;

public:
  GameObject() = default;
  GameObject(hpString name, bool isUpdating = true) noexcept;
  GameObject(hpString name, eComponentFlags flag,
             bool isUpdating = true) noexcept;
  GameObject(hpString name, ComponentBase* comp, bool isUpdating = true) noexcept;

  template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay<CompT>, ComponentBase>>>
  GameObject(hpString name, CompT&& comp) noexcept;

  template <typename... Comps,
    typename = std::enable_if_t<std::is_convertible_v<std::decay<Comps>..., ComponentBase>>>
    GameObject(hpString name, Comps&&... comps) noexcept;

  friend std::ostream& operator<<(std::ostream& ostr, const GameObject& rhs);

public:
  /*static GameObject& Find(hpString name);
  static GameObject& FindGoWithTag(hpString tag);
  static std::vector<GameObject*> FindGosWithTag(hp::hpString tag);*/

public:
  eComponentFlags getComponentFlags() noexcept;
  void setComponentFlags(eComponentFlags flag) noexcept;
  void setComponentFlags(
    std::initializer_list<eComponentFlags>&& flags) noexcept;
  std::vector<NoDeletePtr(ComponentBase)>& getComponentVec();
  void addComponentVec(ComponentBase&& component);

protected:
  eComponentFlags mCompFlags;
  bool mIsUpdating;
  std::vector<std::unique_ptr<ComponentBase>> mComponentVec;
};
};  // namespace hp

#include "GameObject.inl"
