#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace KOD
{

	template <class TObj>
	class QuadTree
	{
		const size_t m_maxDeph = 20;
		size_t m_level = 0;
		const size_t m_maxObjects = 4;
		bool m_isSplited = false;
		sf::Vector2f m_posTopLeft;
		sf::Vector2f m_size;
		std::vector<std::shared_ptr<TObj>> m_objectLsit;
		std::shared_ptr<QuadTree<TObj>> m_topLeft = nullptr;
		std::shared_ptr<QuadTree<TObj>> m_topRight = nullptr;
		std::shared_ptr<QuadTree<TObj>> m_bottomLeft = nullptr;
		std::shared_ptr<QuadTree<TObj>> m_bottomRight = nullptr;

		void split();
		bool isOverlapping(std::shared_ptr<TObj> obj);

	public:
		QuadTree() = delete;
		QuadTree(sf::Vector2f topLeft, sf::Vector2f size, size_t level = 0);
		~QuadTree() = default;
		void addGameObject(std::shared_ptr<TObj> obj);
		void draw(sf::RenderWindow& window);
	};
}

