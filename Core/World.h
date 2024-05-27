#pragma once
#include "export.h"

#include <memory>
#include <unordered_map>
#include "GameObject.h"

namespace kod {

class KOD_API World
{
public:

	World();

	virtual ~World();

	virtual void addGameObject(std::shared_ptr<kod::GameObject> obj);

	virtual void removeGameObject(std::shared_ptr<kod::GameObject> obj);

	virtual void removeGameObject(size_t uid);

	virtual void update(const size_t dt);

	std::unordered_map<size_t, std::shared_ptr<kod::GameObject>>& getObjectList();

private:
	void removaAllObjects();

	std::unordered_map<size_t, std::shared_ptr<kod::GameObject>> m_gameObjects;
};

} // namespace kod
