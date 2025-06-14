#include "Sheaduler.h"

#include <algorithm>
#include <iostream>
#include <syncstream>
#include <chrono>

using time_stamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;

constexpr size_t THREAD_SLEEP_TIME =10;

kod::Scheduler::Scheduler() {}

void kod::Scheduler::stop()
{
	removeAllTasks();
	ThreadHolder::stop();
}

void kod::Scheduler::threadMainLoop()
{
	// TODO: refactor required, std::vector<SheaduledTask> is slow to update
	std::unique_lock lockSheduledTasks(m_sheaduledTasksMutex, std::defer_lock);
	while (getState() == ThreadState::THREAD_STATE_RUNNING) {
		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME));
		lockSheduledTasks.lock();
		for (auto it = m_sheaduledTasks.begin(); it != m_sheaduledTasks.end();) {
			if (it->m_currentTimeout - std::min(THREAD_SLEEP_TIME, it->m_currentTimeout) <= 0) {
				std::unique_lock lockExecutedTasks(m_executedTasksMutex);
				m_tasksToExecute.emplace_back(std::move(*it));
				if (!it->m_isRepeatable) {
					it = m_sheaduledTasks.erase(it);
				} else {
					it->m_currentTimeout = it->m_timeout;
					++it;
				}
			} else {
				it->m_currentTimeout -= std::min(THREAD_SLEEP_TIME, it->m_currentTimeout);
				++it;
			}
		}

		lockSheduledTasks.unlock();
	}
}

void kod::Scheduler::executeTasks()
{
	std::lock_guard lock(m_executedTasksMutex);
	for (auto& task : m_tasksToExecute) {
		task.m_task.execute();
	}
	m_tasksToExecute.clear();
}

void kod::Scheduler::stopAndRemoveTaskById(size_t id)
{
	auto it = std::find_if(m_sheaduledTasks.begin(), m_sheaduledTasks.end(),
	                       [id](SheaduledTask& sheaduledTask) { return sheaduledTask.m_task.getId() == id; });

	if (it != m_sheaduledTasks.end()) {
		m_sheaduledTasks.erase(it);
	}
}

void kod::Scheduler::removeAllTasks()
{
	std::lock_guard lock(m_sheaduledTasksMutex);
	m_sheaduledTasks.clear();
}

size_t kod::Scheduler::addSheaduledTask(kod::TaskFunc taskFunc, size_t timeout, bool isRepeatable)
{
	std::lock_guard lock(m_sheaduledTasksMutex);
	if (getState() != THREAD_STATE_RUNNING) {
		return 0;
	}
	auto task = SheaduledTask(Task(std::move(taskFunc)), timeout, timeout, isRepeatable);
	size_t id = task.m_task.getId();
	m_sheaduledTasks.emplace_back(std::move(task));
	return id;
}
