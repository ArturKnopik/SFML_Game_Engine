#pragma once
#include "export.h"

#include <memory>
#include <unordered_map>
#include "GameObject.h"

namespace kod {

class World
{
public:

	KOD_API World() = default;
	KOD_API virtual ~World();
	KOD_API void addGameObject(std::shared_ptr<kod::GameObject> obj);
	KOD_API void removeGameObject(std::shared_ptr<kod::GameObject> obj);
	KOD_API void removeGameObject(size_t uid);
	KOD_API virtual void update(const size_t dt);
	KOD_API std::unordered_map<size_t, std::shared_ptr<kod::GameObject>>& getObjectList();

private:
	void removaAllObjects();

	std::unordered_map<size_t, std::shared_ptr<kod::GameObject>> m_gameObjects;
};

} // namespace kod
