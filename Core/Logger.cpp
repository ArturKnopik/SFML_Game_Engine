#include "Logger.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

KOD_API kod::Logger g_logger;

void kod::Logger::stop()
{
	m_state.store(kod::Logger::ThreadState::STOPPED);
	m_cv.notify_all();
	if (m_thread.joinable()) {
		m_thread.join();
	}
}

void kod::Logger::setLogLevel(kod::Logger::LogSeverity lvl)
{
	if (lvl > kod::Logger::LogSeverity::ERROR) {
		lvl = kod::Logger::LogSeverity::ERROR;
	}
	m_minLogLevel = lvl;
}

void kod::Logger::setFileNameMaxLenght(size_t fileNameMaxCharacter) { m_fileNameMaxCharacter = fileNameMaxCharacter; }

void kod::Logger::shouldLogToConsole(bool shouldLoogToConsole) { m_consolLog = shouldLoogToConsole; }

void kod::Logger::clearLogFile() { std::remove(m_filename.c_str()); }

void kod::Logger::log(kod::Logger::LogSeverity lvl, const char *message, const std::source_location loc)
{
	std::lock_guard lock(m_mutex);

	if (m_minLogLevel <= lvl) {
		std::string msg = prepareLogMessage(lvl, std::string(message), loc.file_name(), loc.line());
		if (m_consolLog == true) {
			std::cout << msg << std::endl;
		}
		m_queue.push(msg);
		m_cv.notify_one();
	}
}

kod::Logger::Logger() : m_filename("logger.log")
{
	m_state.store(ThreadState::RUNNING);
	m_thread = std::thread(&Logger::logHandler, this);
}

kod::Logger::~Logger() { stop(); }

void kod::Logger::logHandler()
{
	while (ThreadState::RUNNING == m_state.load()) {
		std::unique_lock lock(m_mutex);

		m_cv.wait(lock, [this]() { return !m_queue.empty() || ThreadState::STOPPED == m_state.load(); });

		m_file.open(m_filename, std::ios::out | std::ios::app | std::ios::ate);
		if (!m_file.is_open()) {
			return;
		}

		while (!m_queue.empty()) {
			m_file << m_queue.front() << std::endl;
			m_queue.pop();
		}

		m_file.close();
	}
}

std::string kod::Logger::getSeverityString(kod::Logger::LogSeverity lvl)
{
	switch (lvl) {
		case LogSeverity::INFO:
			return "INFO";
		case LogSeverity::WARNING:
			return "WARNING";
		case LogSeverity::ERROR:
			return "ERROR";
		case LogSeverity::FATAL:
			return "FATAL";
		case LogSeverity::DEBUG:
			return "DEBUG";
		default:
			return "INVALID";
	}
}

std::string kod::Logger::getCurrentTime()
{
	auto timePoint = std::chrono::system_clock::now();
	auto time = std::chrono::system_clock::to_time_t(timePoint);
	std::chrono::system_clock::duration tp = timePoint.time_since_epoch();

	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp);
	auto fractional_seconds = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(tp - seconds);

	std::tm timeInfo;
#ifdef _WIN32
	localtime_s(&timeInfo, &time);
#else
	localtime_r(&time, &timeInfo);
#endif

	std::stringstream ss;
	ss << std::put_time(&timeInfo, "%Y:%d %I:%M:%S") << "." << std::setfill('0') << std::setw(3)
	   << fractional_seconds.count();
	return ss.str();
}

std::string kod::Logger::getCurrentThreadID()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	return ss.str();
}

std::string kod::Logger::formatFileName(const std::string &file)
{
	const size_t threeDotsSize = 3;
	int fileNameMaxCharacter = std::max(static_cast<int>(0), static_cast<int>(m_fileNameMaxCharacter - threeDotsSize));

	if (file.length() >= fileNameMaxCharacter) {
		return "..." + file.substr(file.length() - fileNameMaxCharacter);
	} else {
		return file + std::string(fileNameMaxCharacter - file.length(), ' ');
	}
}

std::string kod::Logger::prepareLogMessage(kod::Logger::LogSeverity lvl, const std::string &message,
                                           const std::string &file, int line)
{
	std::stringstream ss;
	ss << std::setw(10) << getCurrentTime() << " | ";
	ss << std::setw(6) << std::left << getCurrentThreadID() << " |";
	ss << std::setw(8) << std::left << getSeverityString(lvl) << " | ";
	ss << std::setw(m_fileNameMaxCharacter) << std::left << formatFileName(file) << ":" << std::setw(5) << line
	   << " | ";
	ss << message;
	return ss.str();
}

void kod::Logger::join()
{
	if (m_thread.joinable()) {
		m_thread.join();
	}
}