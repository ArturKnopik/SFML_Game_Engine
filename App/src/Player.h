#pragma once

#include "KOD/Animation.h"
#include "KOD/GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"

#include <KOD/IObject.h>

class Player : public KOD::GameObject
{
	sf::RectangleShape rect;
	void input(const size_t dt);

public:
	Player();
	virtual ~Player() = default;
	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(const size_t dt) override;
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
};
