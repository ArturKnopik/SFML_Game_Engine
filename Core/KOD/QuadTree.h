#pragma once

#include "IGameObject.h"
#include <unordered_map>
#include <memory>


namespace KOD
{
	class KOD_API QuadTree
	{
	private:
		std::unordered_map<size_t, std::shared_ptr<IGameObject>> objectMap;

		bool isLeaf = true;
		size_t level = 0;
		size_t capacity;
		size_t maxLevel = 0;
		sf::Vector2i bounds;
		QuadTree* parent = nullptr;
		QuadTree* children[4] = { nullptr };
		std::vector<std::shared_ptr<IGameObject>> objects;
		std::vector<std::shared_ptr<IGameObject>> foundObjects;
		void subdivide();
		void discardEmptyBuckets();
		inline QuadTree* getChild(const sf::Vector2f& bound) const noexcept;
	public:
		QuadTree(){};
		QuadTree(const sf::Vector2f& _bound, size_t _capacity, size_t _maxLevel);
		bool insert(std::shared_ptr<IGameObject>);
		bool remove(std::shared_ptr<IGameObject>);
		bool update(std::shared_ptr<IGameObject>);
		std::vector<std::shared_ptr<IGameObject>>& getObjectsInBound(const sf::Vector2f& bound);
		unsigned totalChildren() const noexcept;
		unsigned totalObjects() const noexcept;
		void clear() noexcept;

	};
}

