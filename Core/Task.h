#pragma once

#include "export.h"

#include <atomic>
#include <functional>

namespace kod {

using TaskFunc = std::function<void(void)>;

static std::atomic<size_t> g_id = 0;

class Task
{
public:
	KOD_API Task() = delete;
	KOD_API ~Task() = default;
	KOD_API Task(TaskFunc&& task);
	KOD_API void execute();
	KOD_API size_t getId();

private:
	TaskFunc task;
	size_t id;
};

} // namespace kod