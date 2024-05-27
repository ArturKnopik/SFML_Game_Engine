#pragma once
#include "IState.h"

#include <memory>
namespace kod {

class KOD_API StateManager
{
public:
	void pushState(std::shared_ptr<kod::IState> state);
	void popState();
	std::shared_ptr<kod::IState> currentState();

private:
	std::vector<std::shared_ptr<kod::IState>> m_states;
};

} // namespace kod
