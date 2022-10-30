#pragma once
#include "IWorld.h"
#include "GameObject.h"

namespace KOD 
{
    using uMapObj = std::unordered_map<size_t, std::shared_ptr<GameObject>>;
    class World :
        public IWorld<GameObject>
    {
        std::unordered_map<size_t, std::shared_ptr<GameObject>> m_gameObjects;
        void removaAllObjects() { m_gameObjects.clear(); }
    public: 
        virtual void addGameObject(std::shared_ptr<GameObject> obj) { m_gameObjects.insert({ obj->getUid(), obj}); }
        virtual void removeGameObject(std::shared_ptr<GameObject> obj) { m_gameObjects.erase(obj->getUid()); }
        virtual void removeGameObject(size_t uid) { m_gameObjects.erase(uid); }
        virtual void update(const size_t dt) override = 0;
        uMapObj& getObjectList() { return m_gameObjects; }
        virtual ~World() { removaAllObjects(); }
    };
}

