#include "PlayerUpdatable.h"

#include "SFML/Window/Keyboard.hpp"

#include <iostream>

//#pragma warning(disable : 4244)

PlayerUpdatable::PlayerUpdatable(sf::Vector2f& position) : m_position(position) {}

void PlayerUpdatable::update(const size_t dt)
{
	float moveSpeed = 0.0004f;
	switch (m_verticalDirection) {
		case Direction::UP:
			m_position.y = m_position.y - (moveSpeed * static_cast<float>(dt));
			break;
		case Direction::DOWN:
			m_position.y = m_position.y + (moveSpeed * static_cast<float>(dt));
			break;
		case Direction::STOP:
			break;
		default:
			break;
	}

	switch (m_horizontalDirection) {
		case Direction::LEFT:
			m_position.x = m_position.x - (moveSpeed * static_cast<float>(dt));
			break;
		case Direction::RIGHT:
			m_position.x = m_position.x + (moveSpeed * static_cast<float>(dt));
			break;
		case Direction::STOP:
			break;
		default:
			break;
	}
}

void PlayerUpdatable::setHorizontalDirection(Direction direction)
{
	if (direction == Direction::LEFT || direction == Direction::RIGHT) {
		m_horizontalDirection = direction;
		return;
	}
	m_horizontalDirection = Direction::STOP;
}

void PlayerUpdatable::setVerticalDirection(Direction direction)
{
	if (direction == Direction::UP || direction == Direction::DOWN) {
		m_verticalDirection = direction;
		return;
	}
	m_verticalDirection = Direction::STOP;
}