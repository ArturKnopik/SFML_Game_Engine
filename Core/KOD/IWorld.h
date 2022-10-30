#include <unordered_map>
#include <memory>

namespace KOD
{
	template <class TObj>
	class IWorld
	{
		std::unordered_map<size_t, std::shared_ptr<TObj>> m_objectsList;
	public:
		IWorld() = default;
		virtual ~IWorld() = default;
		virtual void addGameObject(std::shared_ptr<TObj> obj) = 0 ;
		virtual void removeGameObject(std::shared_ptr<TObj> obj) = 0;
		virtual void removeGameObject(size_t uid) = 0;
		virtual void update(const size_t dt) = 0;
	};
}