#pragma once
#include "export.h"

#include <memory>
#include <unordered_map>
#include "GameObject.h"
#include "Error.h"

namespace kod {

class World
{
public:

	KOD_API World();

	KOD_API virtual ~World();

	KOD_API virtual kod::Error addGameObject(std::shared_ptr<kod::GameObject> obj);

	KOD_API virtual kod::Error removeGameObject(std::shared_ptr<kod::GameObject> obj);

	KOD_API virtual kod::Error removeGameObject(size_t uid);

	KOD_API virtual kod::Error update(const size_t dt);

	KOD_API std::unordered_map<size_t, std::shared_ptr<kod::GameObject>>& getObjectList();

private:
	kod::Error removaAllObjects();

	std::unordered_map<size_t, std::shared_ptr<kod::GameObject>> m_gameObjects;
};

} // namespace kod
