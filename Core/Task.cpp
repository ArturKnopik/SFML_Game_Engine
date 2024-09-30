#include "Task.h"

#include <iostream>
#include <mutex>
#include <syncstream>

kod::Task::Task(kod::TaskFunc&& task)
{
	this->task = std::move(task);
	id = g_id.load();
	g_id.store(++id);
}

void kod::Task::execute()
{
	if (task) {
		task();
	}
}

size_t kod::Task::getId() { return id; }
