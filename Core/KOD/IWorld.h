#include <KOD/GameObject.h>
#include <memory>
#include <unordered_map>

namespace KOD {
template <class TObj>
class KOD_API IWorld
{
	std::unordered_map<size_t, std::shared_ptr<TObj>> m_objectsList;

public:
	IWorld() = default;
	virtual ~IWorld() = default;
	virtual void addGameObject(std::shared_ptr<TObj> obj) = 0;
	virtual void removeGameObject(std::shared_ptr<TObj> obj) = 0;
	virtual void removeGameObject(size_t uid) = 0;
	virtual void update(const size_t dt) = 0;
};
} // namespace KOD