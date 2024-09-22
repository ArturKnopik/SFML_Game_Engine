#include "StateManager.h"

#include "Logger.h"

kod::StateManager::StateManager() {}

void kod::StateManager::pushState(std::shared_ptr<kod::IState> state)
{
	if (!state) {
		g_logger.log(kod::Logger::LogSeverity::ERROR, "Invalid state");
		return;
	}
	m_states.push_back(state);
}

void kod::StateManager::popState()
{
	if (m_states.empty()) {
		g_logger.log(kod::Logger::LogSeverity::ERROR, "Can't pop state");
		return;
	}
	m_states.pop_back();
}

std::shared_ptr<kod::IState> kod::StateManager::currentState()
{
	if (!m_states.empty()) {
		return m_states.back();
	}
	g_logger.log(kod::Logger::LogSeverity::ERROR, "Invalid state, returns nullptr");
	return nullptr;
}
