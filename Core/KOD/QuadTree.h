#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameObject.h"

namespace KOD
{
	template <class TObj>
	class QuadTree
	{
		const size_t m_maxDeph = 20;
		const size_t m_maxObjects = 4;
		size_t m_level = 0;
		bool m_isSplited = false;
		sf::Vector2f m_topLeft;
		sf::Vector2f m_size;
		std::vector<std::shared_ptr<TObj>> m_objectLsit;
		std::shared_ptr<QuadTree<TObj>> m_topLeftLeaf = nullptr;
		std::shared_ptr<QuadTree<TObj>> m_topRightLeaf = nullptr;
		std::shared_ptr<QuadTree<TObj>> m_bottomLeftLeaf = nullptr;
		std::shared_ptr<QuadTree<TObj>> m_bottomRightLeaf = nullptr;

		void split()
		{
			//std::cout << " --== SPLIT ==-- " << std::endl;
			//std::cout << this << " - m_level: " << m_level << std::endl;

			m_isSplited = true;
			size_t newLevel = m_level + 1;

			sf::Vector2f newSize = { m_size.x / 2, m_size.y / 2 };
			//QuadTree(sf::Vector2f topLeft, sf::Vector2f size, size_t level = 0);
			m_topLeftLeaf = std::make_shared < KOD::QuadTree<TObj>>(sf::Vector2f(m_topLeft.x, m_topLeft.y), newSize, newLevel);
			m_topRightLeaf = std::make_shared < KOD::QuadTree<TObj>>(sf::Vector2f{ m_topLeft.x + newSize.x, m_topLeft.y }, newSize, newLevel);
			m_bottomLeftLeaf = std::make_shared < KOD::QuadTree<TObj>>(sf::Vector2f{ m_topLeft.x, m_topLeft.y + newSize.y }, newSize, newLevel);
			m_bottomRightLeaf = std::make_shared < KOD::QuadTree<TObj>>(sf::Vector2f{ m_topLeft.x + newSize.x, m_topLeft.y + newSize.y }, newSize, newLevel);

			for (auto& obj : m_objectLsit)
			{
				if (m_topLeftLeaf->isOverlapping(obj))
				{
					m_topLeftLeaf->addGameObject(obj);
				}
				if (m_topRightLeaf->isOverlapping(obj))
				{
					m_topRightLeaf->addGameObject(obj);
				}
				if (m_bottomLeftLeaf->isOverlapping(obj))
				{
					m_bottomLeftLeaf->addGameObject(obj);
				}
				if (m_bottomRightLeaf->isOverlapping(obj))
				{
					m_bottomRightLeaf->addGameObject(obj);
				}
			}
			m_objectLsit.clear();
		}
		bool isOverlapping(std::shared_ptr<TObj> obj)
		{
			if (obj == nullptr)
			{
				return false;
			}
			// 100,100 - 30,30
			bool isOverlapingX = (obj->getBoundingBox().m_position.x + obj->getBoundingBox().m_size.x > m_topLeft.x &&
				obj->getBoundingBox().m_position.x <= m_topLeft.x + m_size.x);

			bool isOverlapingY = (obj->getBoundingBox().m_position.y + obj->getBoundingBox().m_size.y > m_topLeft.y &&
				obj->getBoundingBox().m_position.y <= m_topLeft.y + m_size.y);
			//std::cout << " ----------------------------------------------------------" << std::endl;
			//std::cout << "obj pos: " << obj->getBoundingBox().m_position.x << ":" << obj->getBoundingBox().m_position.y << std::endl;
			//std::cout << "obj size: " << obj->getBoundingBox().m_size.x << ":" << obj->getBoundingBox().m_size.y << std::endl;
			//std::cout << "window pos: " << m_topLeft.x << ":" << m_topLeft.y << std::endl;
			//std::cout << "window pos: " << m_size.x << ":" << m_size.y << std::endl;
			//std::cout << isOverlapingX << ":" << isOverlapingY << " === " << (isOverlapingX && isOverlapingY) << std::endl;

			return isOverlapingX && isOverlapingY;
		}

	public:
		QuadTree() = delete;
		QuadTree(sf::Vector2f topLeft, sf::Vector2f size, size_t level = 0)
			: m_topLeft(topLeft), m_size(size), m_level(level) {}
		virtual ~QuadTree() = default;
		void clear()
		{
			m_objectLsit.clear();
			m_topLeftLeaf = nullptr;
			m_topRightLeaf = nullptr;
			m_bottomLeftLeaf = nullptr;
			m_bottomRightLeaf = nullptr;
		}
		void addGameObject(std::shared_ptr<TObj> obj)
		{
			//std::cout << " --== addGameObject ==-- " << std::endl;
			if (!obj)
			{
				return;
			}

			if (!isOverlapping(obj))
			{
				return;
			}

			if (m_objectLsit.size() < m_maxObjects && m_isSplited == false || m_level == m_maxDeph)
			{
				m_objectLsit.push_back(obj);
			}
			else
			{
				split();
				m_objectLsit.clear();

				if (m_topLeftLeaf->isOverlapping(obj))
				{
					m_topLeftLeaf->addGameObject(obj);
				}
				if (m_topRightLeaf->isOverlapping(obj))
				{
					m_topRightLeaf->addGameObject(obj);
				}
				if (m_bottomLeftLeaf->isOverlapping(obj))
				{
					m_bottomLeftLeaf->addGameObject(obj);
				}
				if (m_bottomRightLeaf->isOverlapping(obj))
				{
					m_bottomRightLeaf->addGameObject(obj);
				}

			}
		}
		void drawQT(sf::RenderWindow& window)
		{
			if (m_isSplited == true)
			{
				m_topLeftLeaf->drawQT(window);
				m_topRightLeaf->drawQT(window);
				m_bottomLeftLeaf->drawQT(window);
				m_bottomRightLeaf->drawQT(window);
				double x = m_topLeft.x;
				double y = m_topLeft.y;
				sf::RectangleShape rectangle;
				rectangle.setPosition(sf::Vector2f(x, y));
				rectangle.setSize(sf::Vector2f(m_size.x, m_size.y));
				rectangle.setFillColor(sf::Color(255, 0, 0, 15));
				rectangle.setOutlineThickness(1);
				window.draw(rectangle);
			}
			else
			{
				double x = m_topLeft.x;
				double y = m_topLeft.y;
				sf::RectangleShape rectangle;
				rectangle.setPosition(sf::Vector2f(x, y));
				rectangle.setSize(m_size);
				rectangle.setFillColor(sf::Color(255, 0, 0, 15));
				rectangle.setOutlineThickness(1);
				window.draw(rectangle);
				for (auto& it : m_objectLsit)
				{
					sf::RectangleShape rectangle;
					rectangle.setPosition(it->getBoundingBox().m_position);
					rectangle.setSize(it->getBoundingBox().m_size);
					rectangle.setOutlineColor(sf::Color::Green);
					rectangle.setOutlineThickness(1);
					rectangle.setFillColor(sf::Color(0, 255, 0, 30));
					window.draw(rectangle);
				}
			}
		}

		QuadTree& operator=(const QuadTree<TObj>& rhs)
		{
			return *this;
		}
	};
}