#include "Player.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Keyboard.hpp"

void Player::input(const size_t dt)
{
	auto pos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		setPosition({pos.x, pos.y - static_cast<float>(dt * 0.0001)});
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		setPosition({pos.x, pos.y + static_cast<float>(dt * 0.0001)});
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		setPosition({pos.x - static_cast<float>(dt * 0.0001), pos.y});
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		setPosition({pos.x + static_cast<float>(dt * 0.0001), pos.y});
	}
}

Player::Player()
{
	rect = sf::RectangleShape(sf::Vector2f({10, 10}));
	rect.setFillColor(sf::Color::Red);
}

void Player::draw(sf::RenderWindow& window) { window.draw(rect); }

void Player::update(const size_t dt)
{
	input(dt);
	updateBoundingBox(getPosition(), {10, 10});
	// std::cout << getPosition().x << ":" << getPosition().y << std::endl;
}

void Player::setPosition(sf::Vector2f pos) { rect.setPosition(pos); }

sf::Vector2f Player::getPosition() { return rect.getPosition(); }
