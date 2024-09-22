#pragma once
#include "export.h"

#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <source_location>
#include <string>
#include <thread>

namespace kod {

class Logger
{
public:
	enum class ThreadState
	{
		RUNNING,
		STOPPED
	};

	enum class LogSeverity
	{
		DEBUG = 0,
		INFO = 1,
		WARNING = 2,
		ERROR = 3,
		FATAL = 4,
	};

	KOD_API Logger();
	KOD_API ~Logger();
	KOD_API void log(kod::Logger::LogSeverity lvl, const char* message,
	                 const std::source_location loc = std::source_location::current());

	KOD_API void setLogLevel(kod::Logger::LogSeverity lvl);
	KOD_API void setFileNameMaxLenght(size_t fileNameMaxCharacter);
	KOD_API void shouldLogToConsole(bool shouldLoogToConsole);
	KOD_API void clearLogFile();

	KOD_API void join();
	KOD_API void stop();

private:
	void logHandler();
	std::string getSeverityString(kod::Logger::LogSeverity lvl);
	std::string getCurrentTime();
	std::string getCurrentThreadID();
	std::string formatFileName(const std::string& file);
	std::string prepareLogMessage(kod::Logger::LogSeverity lvl, const std::string& message, const std::string& file,
	                              int line);

	kod::Logger::LogSeverity m_minLogLevel = kod::Logger::LogSeverity::FATAL;
	std::string m_filename;
	std::ofstream m_file;
	std::thread m_thread;
	std::condition_variable_any m_cv;
	std::queue<std::string> m_queue;
	std::atomic<kod::Logger::ThreadState> m_state = kod::Logger::ThreadState::RUNNING;
	size_t m_fileNameMaxCharacter = 45;
	std::recursive_mutex m_mutex;
	bool m_consolLog = true;
	bool m_shouldCleanFileOnStartup = false;
};

} // namespace kod

KOD_API extern kod::Logger g_logger;