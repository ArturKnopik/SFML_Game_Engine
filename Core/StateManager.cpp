#include "StateManager.h"

void kod::StateManager::pushState(std::shared_ptr<kod::IState> state)
{
	if (state) {
		m_states.push_back(state);
	}
}

void kod::StateManager::popState()
{
	if (!m_states.empty()) {
		m_states.pop_back();
	}
}

std::shared_ptr<kod::IState> kod::StateManager::currentState()
{
	if (!m_states.empty()) {
		return m_states.back();
	}
	return nullptr;
}
