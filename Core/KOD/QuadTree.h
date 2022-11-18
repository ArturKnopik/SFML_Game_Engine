#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameObject.h"
#include "KOD/UtilityTools.h"

namespace KOD
{
	template <class TObj>
	class QuadTreeNode : public std::enable_shared_from_this<QuadTreeNode<TObj>>
	{
		const size_t m_maxDeph = 13;
		const size_t m_maxObjects = 4;
		size_t m_level = 0;
		bool m_isSplited = false;
		sf::Vector2f m_topLeft;
		sf::Vector2f m_size;
		sf::RectangleShape m_rectShape;
		std::vector<std::shared_ptr<TObj>> m_objectLsit;
		std::shared_ptr<QuadTreeNode<TObj>> m_topLeftLeaf = nullptr;
		std::shared_ptr<QuadTreeNode<TObj>> m_topRightLeaf = nullptr;
		std::shared_ptr<QuadTreeNode<TObj>> m_bottomLeftLeaf = nullptr;
		std::shared_ptr<QuadTreeNode<TObj>> m_bottomRightLeaf = nullptr;
	public:
		QuadTreeNode() = delete;
		QuadTreeNode(sf::Vector2f topLeft, sf::Vector2f size, size_t level = 0)
			: m_topLeft(topLeft), m_size(size), m_level(level)
		{
			m_rectShape.setPosition(topLeft);
			m_rectShape.setSize(size);
			m_rectShape.setFillColor(sf::Color(0, 250 - (level * 15), 0 + (level * 15), 10));
			m_rectShape.setOutlineColor(sf::Color::White);
			m_rectShape.setOutlineThickness(1);
			m_objectLsit.reserve(4);
		}
		virtual ~QuadTreeNode() = default;
		void split()
		{
			m_isSplited = true;
			size_t newLevel = m_level + 1;

			sf::Vector2f newSize = { m_size.x / 2, m_size.y / 2 };
			m_topLeftLeaf = std::make_shared < KOD::QuadTreeNode<TObj>>(sf::Vector2f(m_topLeft.x, m_topLeft.y), newSize, newLevel);
			m_topRightLeaf = std::make_shared < KOD::QuadTreeNode<TObj>>(sf::Vector2f{ m_topLeft.x + newSize.x, m_topLeft.y }, newSize, newLevel);
			m_bottomLeftLeaf = std::make_shared < KOD::QuadTreeNode<TObj>>(sf::Vector2f{ m_topLeft.x, m_topLeft.y + newSize.y }, newSize, newLevel);
			m_bottomRightLeaf = std::make_shared < KOD::QuadTreeNode<TObj>>(sf::Vector2f{ m_topLeft.x + newSize.x, m_topLeft.y + newSize.y }, newSize, newLevel);

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

			bool isOverlapingX = (obj->getBoundingBox().m_position.x + obj->getBoundingBox().m_size.x >= m_topLeft.x &&
				obj->getBoundingBox().m_position.x <= m_topLeft.x + m_size.x);

			bool isOverlapingY = (obj->getBoundingBox().m_position.y + obj->getBoundingBox().m_size.y >= m_topLeft.y &&
				obj->getBoundingBox().m_position.y <= m_topLeft.y + m_size.y);
			return isOverlapingX && isOverlapingY;
		}

		bool isOverlapping(KOD::BoundingBox bb)
		{

			bool isOverlapingX = (bb.m_position.x + bb.m_size.x >= m_topLeft.x &&
				bb.m_position.x <= m_topLeft.x + m_size.x);

			bool isOverlapingY = (bb.m_position.y + bb.m_size.y >= m_topLeft.y &&
				bb.m_position.y <= m_topLeft.y + m_size.y);
			return isOverlapingX && isOverlapingY;
		}

		void addGameObject(std::shared_ptr<TObj> obj)
		{
			if (!obj)
			{
				return;
			}

			if (!isOverlapping(obj))
			{
				return;
			}

			if (m_objectLsit.size() < m_maxObjects && m_isSplited == false && m_isSplited == false || m_level == m_maxDeph)
			{
				m_objectLsit.push_back(obj);
			}
			else
			{
				if (m_isSplited == false)
				{
					split();
				}
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

		size_t getObjectCount()
		{
			size_t count = 0;
			if (m_isSplited)
			{
				if (m_topLeftLeaf)
				{
					count += m_topLeftLeaf->getObjectCount();
				}
				if (m_topRightLeaf)
				{
					count += m_topRightLeaf->getObjectCount();
				}
				if (m_bottomLeftLeaf)
				{
					count += m_bottomLeftLeaf->getObjectCount();
				}
				if (m_bottomRightLeaf)
				{
					count += m_bottomRightLeaf->getObjectCount();
				}
			}
			else
			{
				count = m_objectLsit.size();
			}
			return count;
		}

		void drawNode(sf::RenderWindow& window)
		{
			window.draw(m_rectShape);
			if (m_isSplited)
			{
				if (m_topLeftLeaf)
				{
					m_topLeftLeaf->drawNode(window);
				}
				if (m_topRightLeaf)
				{
					m_topRightLeaf->drawNode(window);
				}
				if (m_bottomLeftLeaf)
				{
					m_bottomLeftLeaf->drawNode(window);
				}
				if (m_bottomRightLeaf)
				{
					m_bottomRightLeaf->drawNode(window);
				}
			}
		}

		std::vector<std::shared_ptr<KOD::QuadTreeNode<TObj>>> getNodesInArea(KOD::BoundingBox bb)
		{
			std::vector<std::shared_ptr<KOD::QuadTreeNode<TObj>>> nodeArray;
			if (m_isSplited)
			{
				if (m_topLeftLeaf)
				{
					if (m_topLeftLeaf->isOverlapping(bb))
					{
						KOD::addVectors(nodeArray, m_topLeftLeaf->getNodesInArea(bb));
					}
				}
				if (m_topRightLeaf)
				{
					if (m_topRightLeaf->isOverlapping(bb))
					{
						KOD::addVectors(nodeArray, m_topRightLeaf->getNodesInArea(bb));
					}
				}
				if (m_bottomLeftLeaf)
				{
					if (m_bottomLeftLeaf->isOverlapping(bb))
					{
						KOD::addVectors(nodeArray, m_bottomLeftLeaf->getNodesInArea(bb));
					}
				}
				if (m_bottomRightLeaf)
				{
					if (m_bottomRightLeaf->isOverlapping(bb))
					{
						KOD::addVectors(nodeArray, m_bottomRightLeaf->getNodesInArea(bb));
					}
				}
			}
			else
			{
				nodeArray.push_back(this->shared_from_this());
			}
			return nodeArray;
		}
	};

	template <class TObj>
	class QuadTree : std::enable_shared_from_this<QuadTree<TObj>>
	{
		const size_t m_maxDeph = 13;
		const size_t m_maxObjects = 4;
		size_t m_level = 0;
		bool m_isSplited = false;
		sf::Vector2f m_topLeft;
		sf::Vector2f m_size;
		std::vector<std::shared_ptr<TObj>> m_objectLsit;
		std::shared_ptr<QuadTreeNode<TObj>> m_qTreeNode = nullptr;


	public:
		QuadTree() = delete;
		QuadTree(sf::Vector2f topLeft, sf::Vector2f size, size_t level = 0)
			: m_topLeft(topLeft), m_size(size), m_level(level), m_qTreeNode(std::make_shared<QuadTreeNode<TObj>>(topLeft, size, level)) {}
		virtual ~QuadTree() = default;
		void clear()
		{
			m_qTreeNode = std::make_shared<QuadTreeNode<TObj>>(m_topLeft, m_size, m_level);
		}

		void addGameObject(std::shared_ptr<TObj> obj)
		{
			if (!obj)
			{
				return;
			}

			m_qTreeNode->addGameObject(obj);
		}

		void drawQT(sf::RenderWindow& window)
		{
			m_qTreeNode->drawNode(window);
		}

		size_t getObjectCount()
		{
			return m_qTreeNode->getObjectCount();
		}

		QuadTree& operator=(const QuadTree<TObj>& rhs)
		{
			return *this;
		}

		std::vector<std::shared_ptr<KOD::QuadTreeNode<TObj>>> getNodesInArea(KOD::BoundingBox bb)
		{
			return m_qTreeNode->getNodesInArea(bb);
		}

		std::vector<std::shared_ptr<KOD::QuadTreeNode<TObj>>> getAllNodes()
		{
			KOD::BoundingBox bb;
			bb.m_position = m_topLeft;
			bb.m_size = m_size;
			return m_qTreeNode->getNodesInArea(bb);
		}




		/*
		std::vector <std::shared_ptr<KOD::QuadTree<TObj>>> getAllActiveNodes()
		{
			std::vector< std::shared_ptr<KOD::QuadTree<TObj>>> nodeVector;
			if (this->m_isSplited == true)
			{
				if (m_topLeftLeaf)
				{
					KOD::addVectors<std::shared_ptr<KOD::QuadTree<TObj>>>(nodeVector, m_topLeftLeaf->getAllActiveNodes());
				}
				if (m_topRightLeaf)
				{
					KOD::addVectors<std::shared_ptr<KOD::QuadTree<TObj>>>(nodeVector, m_topRightLeaf->getAllActiveNodes());
				}
				if (m_bottomLeftLeaf)
				{
					KOD::addVectors<std::shared_ptr<KOD::QuadTree<TObj>>>(nodeVector, m_bottomLeftLeaf->getAllActiveNodes());
				}
				if (m_bottomRightLeaf)
				{
					KOD::addVectors<std::shared_ptr<KOD::QuadTree<TObj>>>(nodeVector, m_bottomRightLeaf->getAllActiveNodes());
				}
			}
			else
			{
				if (m_level != 0)
				{
					nodeVector.push_back(this->shared_from_this());
				}
			}
			return nodeVector;
		}
		*/
	};
}