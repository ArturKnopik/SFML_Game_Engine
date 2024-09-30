#pragma once
#include "GameObject.h"
#include "SFML/Window/Event.hpp"
#include "export.h"

#include <memory>
#include <unordered_map>
#include "Gui.h"

namespace kod {

class Game;

class IState
{
public:
	KOD_API IState() = delete;
	KOD_API IState(Game& game);
	KOD_API virtual ~IState() = default;
	KOD_API virtual void draw() = 0;
	KOD_API virtual void drawGui();
	KOD_API virtual void update(const size_t dt) = 0;
	KOD_API virtual void updateGui(const size_t dt);
	KOD_API virtual void input(sf::Event& event);
	KOD_API virtual void inputGui(sf::Event& event);
	KOD_API virtual void input();
	KOD_API void addGameObject(std::shared_ptr<kod::GameObject> object);
	KOD_API void removeGameObject(std::shared_ptr<kod::GameObject> object);
	KOD_API void removeGameObject(uint64_t uid);
	KOD_API void addGuiElement(std::shared_ptr<kod::Widget> uiElement);
	KOD_API void removeGuiElement(std::shared_ptr<kod::Widget> uiElement);

protected:
	Game& m_game;
	std::unordered_map<uint64_t, std::shared_ptr<kod::GameObject>> m_gameObjects;
	kod::Gui m_gui;
};

} // namespace kod