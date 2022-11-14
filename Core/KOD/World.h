#pragma once
#include "IWorld.h"
#include "GameObject.h"
#include "QuadTree.h"

namespace KOD
{
	class KOD_API World :
		public IWorld<KOD::GameObject>
	{
		std::unordered_map<size_t, std::shared_ptr<KOD::GameObject>> m_gameObjects;

		void removaAllObjects() { m_gameObjects.clear(); }
	public:
		QuadTree<KOD::GameObject> m_qTree;
		World() = delete;

		World(BoundingBox qTreeArea)
			:m_qTree(KOD::QuadTree<KOD::GameObject>(qTreeArea.m_position, qTreeArea.m_size, 0)) { }

		virtual ~World() { removaAllObjects(); }

		virtual void addGameObject(std::shared_ptr<KOD::GameObject> obj)
		{
			if (!obj)
			{
				return;
			}
			m_gameObjects.insert({ obj->getUid(), obj });
		}

		virtual void removeGameObject(std::shared_ptr<KOD::GameObject> obj)
		{
			if (!obj)
			{
				return;
			}
			m_gameObjects.erase(obj->getUid());
		}

		virtual void removeGameObject(size_t uid)
		{
			m_gameObjects.erase(uid);
		}

		virtual void update(const size_t dt) override {};
		std::unordered_map<size_t, std::shared_ptr<KOD::GameObject>>& getObjectList()
		{
			return m_gameObjects;
		}
	};
}
