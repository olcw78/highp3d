#pragma once

#include <vector>

#include "hpObject.h"
#include "hpString.h"
#include "hpMacro.h"

namespace hp {
enum class eComponentFlags {
	NONE = 0x01,

	TRANSFORM = 0x02,
	RENDERER = 0x04,
	INPUT = 0x08,
	CAMERA = 0x16,
	PHYSICS = 0x32,
	/*SCENE = 1 << 6,
	TIMER = 1 << 7,*/
	__LAST = PHYSICS << 1
};

MAKE_ENUM_FLAGS_FUNC(eComponentFlags)

class ComponentBase : public hpObject {
	using ComponentVec = std::vector<std::unique_ptr<ComponentBase>>;

public:
	using hpObject::hpObject;
	ComponentBase() = default;
	bool operator<(const ComponentBase& comp) noexcept;
	bool operator>(const ComponentBase& comp) noexcept;
	bool operator==(const ComponentBase& comp) noexcept;

public:
	virtual bool destroy_self(float delay = 0.0f) override;

public:
	hpString get_tag() const noexcept;
	void set_tag(hpString&& str) noexcept;
	ComponentVec& get_components_vec() noexcept;
	void set_component_flag(eComponentFlags flag) noexcept;
	eComponentFlags get_component_flag() const noexcept;
	bool is_enabled() const noexcept;
	void set_enabled(bool flag) noexcept;

	template <typename CompareT>
	bool is_convertible_type();

	template <typename CompareT>
	bool is_convertible_type(CompareT&& comp);

protected:
	hpString mTag;
	eComponentFlags mFlag;
	ComponentVec mComponentVec;
	bool mIsEnabled = false;
};
};  // namespace hp

#include "hpComponentBase.inl"
