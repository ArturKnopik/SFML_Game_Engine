#include "QuadTree.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

template<class TObj>
void KOD::QuadTree<TObj>::split()
{
	if (m_level >= m_maxDeph)
	{
		return;
	}

	m_isSplited = true;
	
	sf::Vector2f newSize = { m_size.x / 2, m_size.y / 2 }
	m_topLeft = std::make_shared <QuadTree<TObj>({ m_posTopLeft.x, m_posTopLeft.y}, newSize, m_level + 1);

	m_topRight = std::make_shared < QuadTree<TObj>({ m_posTopLeft.x + newSize.x, m_posTopLeft.y}, newSize, level + 1);

	m_bottomLeft = std::make_shared < QuadTree<TObj>({ m_posTopLeft.x, m_posTopLeft.y + newSize.x + y}, newSize, level + 1);

	m_bottomRight = std::make_shared < QuadTree<TObj>({ m_posTopLeft.x + newSize.x, m_posTopLeft.y + newSize.y }, newSize, level + 1);

	for (auto& obj : m_objectLsit)
	{
		if (m_topLeft->isOverlapping(obj))
		{
			m_topLeft->addGameObject(obj);
		}
		if (m_topRight->isOverlapping(obj))
		{
			m_topRight->addGameObject(obj);
		}
		if (m_bottomLeft->isOverlapping(obj))
		{
			m_bottomLeft->addGameObject(obj);
		}
		if (m_bottomRight->isOverlapping(obj));
		{
			m_bottomRight->addGameObject(obj);
		}
	}
	m_objectLsit.clear();
}


template<class TObj>
KOD::QuadTree<TObj>::QuadTree(sf::Vector2f topLeft, sf::Vector2f size, size_t level)
	: m_topLeft(topLeft), m_size(size), m_level(level)
{
}

template<class TObj>
void KOD::QuadTree<TObj>::addGameObject(std::shared_ptr<TObj> obj)
{
	if (!isOverlapping(gameObjectPrt))
	{
		return;
	}

	if (m_objectLsit.size() < m_maxItemInQuadTree || level == m_maxDeph) //TODO: remove hard coded variable
	{
		m_objectLsit.push_back(gameObjectPrt);
	}
	else
	{

		if (m_isSplited == false)
		{
			split();
			m_objectLsit.clear();
			m_objectLsit.resize(0);
		}
		if (m_topLeft->isOverlapping(gameObjectPrt))
		{
			m_topLeft->addGameObject(gameObjectPrt);
		}
		if (m_topRight->isOverlapping(gameObjectPrt))
		{
			m_topRight->addGameObject(gameObjectPrt);
		}
		if (m_bottomLeft->isOverlapping(gameObjectPrt))
		{
			m_bottomLeft->addGameObject(gameObjectPrt);
		}
		if (m_bottomRight->isOverlapping(gameObjectPrt))
		{
			m_bottomRight->addGameObject(gameObjectPrt);
		}

	}
}

template<class TObj>
void KOD::QuadTree<TObj>::draw(sf::RenderWindow& window)
{
	if (m_isSplited == true)
	{

		m_topLeft->draw(window);
		m_topRight->draw(window);
		m_bottomLeft->draw(window);
		m_bottomRight->draw(window);
		double x = m_posTopLeft.x;
		double y = m_posTopLeft.y;
		sf::RectangleShape rectangle;
		rectangle.setPosition(sf::Vector2f(x, y));
		rectangle.setSize(sf::Vector2f(m_size.x, m_size.y));
		rectangle.setFillColor(sf::Color(255, 0, 0, 15));
		rectangle.setOutlineThickness(1);
		window->draw(rectangle);
	}
	else
	{
		double x = m_posTopLeft.x;
		double y = m_posTopLeft.y;
		sf::RectangleShape rectangle;
		rectangle.setPosition(sf::Vector2f(x, y));
		rectangle.setSize(m_size);
		rectangle.setFillColor(sf::Color(255, 0, 0, 15));
		rectangle.setOutlineThickness(1);
		window->draw(rectangle);
		for (auto& it : m_objectLsit)
		{
			sf::RectangleShape rectangle;
			rectangle.setPosition(it->getBoundingBox().m_position);
			rectangle.setSize(it->getBoundingBox().m_size);
			rectangle.setOutlineColor(sf::Color::Green);
			rectangle.setOutlineThickness(1);
			rectangle.setFillColor(sf::Color(0, 255, 0, 30));
			window->draw(rectangle);
		}
	}
}

template<class TObj>
bool KOD::QuadTree<TObj>::isOverlapping(std::shared_ptr<TObj> obj)
{
	if (obj == nullptr)
	{
		return false;
	}
	//TODO: fix me
	/*
	double x = m_posTopLeft - m_width / 2;
	double y = m_centerY - m_height / 2;

	if (gameObjectPrt->getBoundingBox().m_position.x < m_posTopLeft.x + m_width &&
		gameObjectPrt->getBoundingBox().m_position.x + gameObjectPrt->getBoundingBox().m_size.x > m_posTopLeft.x &&
		gameObjectPrt->getBoundingBox().m_position.y < m_posTopLeft.y + m_height &&
		gameObjectPrt->getBoundingBox().m_position.y + gameObjectPrt->getBoundingBox().m_size.y > m_posTopLeft.y)
	{
		return true;
	}
	*/
	return true;
}
