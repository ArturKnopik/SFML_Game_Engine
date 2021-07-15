#pragma once
#include "KOD_export.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <utility>

#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )

namespace KOD
{
	class IGameState;
	struct Settings;
	class KOD_API Game
	{
	private:
		std::vector<std::shared_ptr<IGameState>> m_states;
	public:
		sf::RenderWindow m_window;
		Game();
		Game(const KOD::Settings settings);
		~Game();
		void pushState(std::shared_ptr<IGameState> state);
		void popState();
		std::shared_ptr<IGameState> currentState();
		void gameLoop();
		sf::RenderWindow & getRenderWindow();
	};
}
