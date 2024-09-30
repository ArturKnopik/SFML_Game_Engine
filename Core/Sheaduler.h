#pragma once

#include "Task.h"
#include "ThreadHolderBase.h"

#include <mutex>
#include <queue>

namespace kod {

struct SheaduledTask
{
	Task m_task;
	size_t m_currentTimeout;
	size_t m_timeout;
	bool m_isRepeatable = false;
};

struct Compare
{
	bool operator()(const SheaduledTask l, const SheaduledTask r) const
	{
		return l.m_currentTimeout > r.m_currentTimeout;
	}
};

class Scheduler : public ThreadHolder<Scheduler>
{
public:
	KOD_API Scheduler();
	KOD_API void threadMainLoop();
	KOD_API void executeTasks();
	KOD_API void stopAndRemoveTaskById(size_t id);
	KOD_API size_t addSheaduledTask(TaskFunc taskFunc, size_t timeout, bool isRepeatable = false);
	KOD_API void stop();

private:
	void removeAllTasks();

	std::mutex m_sheaduledTasksMutex;
	std::mutex m_executedTasksMutex;
	std::vector<SheaduledTask> m_sheaduledTasks;
	std::vector<SheaduledTask> m_tasksToExecute;
};

} // namespace kod