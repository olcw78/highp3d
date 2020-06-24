#pragma once

#pragma once

#include <sstream>

#include "hpDebug.h"
#include "hpMacro.h"

#include "hpObjectHelper.h"
#include "hpString.h"

namespace hp {
class hpObject {
public:
	friend class hpObjectHelper;
	hpObject() noexcept;

	//Object(glm::vec3 pos = glm::vec3{0.0f}, glm::quat rot = glm::quat{0.0f}) noexcept;
	hpObject(hpString&& str) noexcept;
	/*template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, Object>>>
	Object(CompT&& obj) noexcept;*/

	hpObject(const hpObject&) noexcept = default;
	hpObject(hpObject&&) noexcept = default;
	hpObject& operator=(const hpObject&) noexcept = default;
	hpObject& operator=(hpObject&&) noexcept = default;
	virtual ~hpObject() noexcept = default;

	friend std::ostream& operator<<(std::ostream& ostr,
																	const hpObject& obj) noexcept;
	friend std::istream& operator>>(std::istream&, const hpObject&) = delete;

	bool operator==(const hpObject& ref) noexcept;

public:
	template <typename CompT, typename = std::enable_if_t<std::is_convertible_v<std::decay_t<CompT>, hpObject>>>
	static CompT Instantiate(CompT&& obj);

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
	static bool Destroy(const hpObject& ref, float delay = 0.0f);

	virtual hpString ToStr() const noexcept;

public:
	unsigned getInstanceId() const noexcept;
	hpString getName() const noexcept;
	void setName(hpString&& name);

protected:
	unsigned mInstanceId;
	hpString mName;
};
};  // namespace hp

#include "hpObject.inl"
