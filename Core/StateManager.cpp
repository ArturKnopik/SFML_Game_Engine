#include "StateManager.h"

kod::StateManager::StateManager() {}

kod::Error kod::StateManager::pushState(std::shared_ptr<kod::IState> state)
{
	m_states.push_back(state);
	return Error::OK;
}

kod::Error kod::StateManager::popState()
{
	if (m_states.empty()) {
		return Error::MEMORY;
	}
	m_states.pop_back();
	return Error::OK;
}

std::shared_ptr<kod::IState> kod::StateManager::currentState()
{
	if (!m_states.empty()) {
		return m_states.back();
	}
	return nullptr;
}
