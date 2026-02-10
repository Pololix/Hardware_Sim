#pragma once

#include <utility>
#include <string>
#include <iostream>
#include <unordered_map>

namespace debug_utils
{
enum class LogLevel : uint8_t
{
	DEBUG,
	INFO,
	WARNING,
	ERROR
};

class Logger
{
public:
	Logger(LogLevel minLevel)
		: m_minLevel(minLevel) {}
	~Logger() = default;

	template<typename F>
	void log(LogLevel level, F&& stringFunc) const
	{
		if (level < m_minLevel) return;

		std::string msg = std::forward<F>(stringFunc)();
		std::cout << "[" << level << "]: " << msg << '\n';
	}
private:
	LogLevel m_minLevel;
};

inline Logger& getLogger(const std::string& name)
{
	static std::unordered_map<std::string, Logger> loggerMap {};

	if (!loggerMap.contains(name))
	{
		loggerMap.emplace(name, Logger(LogLevel::DEBUG));
	}

	return loggerMap.at(name);
}
}