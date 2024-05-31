#pragma once
#include "Error.h"
#include "GameObject.h"
#include "SFML/Window/Event.hpp"
#include "export.h"

#include <memory>
#include <unordered_map>

namespace kod {

class Game;

class IState
{
public:
	KOD_API IState() = delete;
	KOD_API IState(Game& game);
	KOD_API virtual ~IState() = default;
	KOD_API virtual kod::Error draw() = 0;
	KOD_API virtual kod::Error update(const size_t dt) = 0;
	KOD_API virtual kod::Error input(sf::Event& event) = 0;
	KOD_API kod::Error addGameObject(std::shared_ptr<kod::GameObject> object);
	KOD_API kod::Error removeGameObject(std::shared_ptr<kod::GameObject> object);
	KOD_API kod::Error removeGameObject(uint64_t uid);

protected:
	Game& m_game;
	std::unordered_map<uint64_t, std::shared_ptr<kod::GameObject>> m_gameObjects;
};

} // namespace kod