#pragma once
#include "KOD_export.h"
#include "SFML/Graphics.hpp"
#include "UiHandler.h"

#include <memory>
#include <utility>
#include <vector>

#pragma warning(disable : 4251)
#pragma warning(disable : 4244)

// TODO: create change to true singleton

namespace KOD {
class IState;
struct Settings;

class KOD_API Game
{
private:
	std::vector<std::shared_ptr<IState>> m_states;
	sf::RenderWindow m_window;
	KOD::UiHandler m_uiHandler;

public:
	Game();
	Game(const KOD::Settings settings);
	~Game();
	void pushState(std::shared_ptr<IState> state);
	void popState();
	std::shared_ptr<IState> currentState();
	void gameLoop();
	sf::RenderWindow& getRenderWindow();
};
} // namespace KOD
