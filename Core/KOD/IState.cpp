
#include "IState.h"

KOD::IState::IState(std::shared_ptr<KOD::Game> game)
	:m_game(game)
{
	if (!m_game.lock()) { std::cerr << "Game obj not set!!!" << std::endl; }
}
