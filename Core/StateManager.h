#pragma once
#include "IState.h"

#include <memory>
#include <vector>

namespace kod {

class StateManager
{
public:
	KOD_API StateManager();
	KOD_API void pushState(std::shared_ptr<kod::IState> state);
	KOD_API void popState();
	KOD_API std::shared_ptr<kod::IState> currentState();

private:
	std::vector<std::shared_ptr<kod::IState>> m_states;
};

} // namespace kod
