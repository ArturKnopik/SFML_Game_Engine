#include "game.h"

#include <StateManager.h>
#include <iostream>

class State : public kod::IState
{
public:
	State(kod ::Game &game) : kod::IState(game) {}
	kod::Error draw() override { return kod::Error::OK; }
	kod::Error update(const size_t dt) override { return kod::Error::OK; }
	kod::Error input(sf::Event &event) override { return kod::Error::OK; }
};

int main()
{
	auto &game = kod::Game::getInstance();
	game.pushState(std::make_shared<State>(game));
	game.run();
}