#pragma once
#include "IWorld.h"
#include "GameObject.h"
#include "QuadTree.h"

namespace KOD 
{
    using uMapObj = std::unordered_map<size_t, std::shared_ptr<GameObject>>;
    class World :
        public IWorld<GameObject>
    {
        QuadTree<KOD::GameObject> m_qTree;
        std::unordered_map<size_t, std::shared_ptr<GameObject>> m_gameObjects;
        void removaAllObjects() { m_gameObjects.clear(); }
    public: 
        World() = delete;
        World(BoundingBox qTreeSize);
        virtual ~World() { removaAllObjects(); }
        virtual void addGameObject(std::shared_ptr<GameObject> obj);
        virtual void removeGameObject(std::shared_ptr<GameObject> obj);
        virtual void removeGameObject(size_t uid);
        virtual void update(const size_t dt) override = 0;
        uMapObj& getObjectList();
    };
}

