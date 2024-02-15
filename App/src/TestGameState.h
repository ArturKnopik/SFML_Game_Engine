#pragma once
#include "KOD/GameObject.h"
#include "Player.h"

#include <KOD/IState.h>
#include <KOD/World.h>
static size_t g_dt = 0; // hack for input calculations

class TestGameState : public KOD::IState, public KOD::World
{
private:
	std::shared_ptr<Player> m_player;
	sf::Event m_event;
	void printTestMassage();
	void checkCollision();
	// bool compareObjectUid(std::shared_ptr<KOD::IGameObject> left, std::shared_ptr<KOD::IGameObject> right);
public:
	TestGameState() = delete;
	TestGameState(std::shared_ptr<KOD::Game> game);
	virtual void draw();
	virtual void input() override;
	virtual void update(const size_t dt) override;
	virtual ~TestGameState();
};
