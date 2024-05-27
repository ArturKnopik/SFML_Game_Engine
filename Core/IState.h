#pragma once
#include "Game.h"

#include <memory>
#include <unordered_map>

namespace kod {

class KOD_API IState
{
public:
	IState() = delete;
	IState(std::shared_ptr<kod::Game> game);
	virtual ~IState() = default;
	virtual void draw() = 0;
	virtual void update(const size_t dt) = 0;
	virtual void input() = 0;

protected:
	std::weak_ptr<kod::Game> m_game;
};
} // namespace KOD
