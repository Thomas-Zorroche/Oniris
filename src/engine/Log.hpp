#pragma once

enum class LogLevel
{
	NONE = 0, INFO, WARNING, ERROR
};

class Log
{
public:
	// Static method to get the only instance shared by the class
	static Log& Get()
	{
		static Log instance;
		return instance;
	}

	LogLevel Level() const { return _logLevel; }
	void SetLevel(LogLevel level) { _logLevel = level; }

	// Delete copy constructor and = operator
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

private:
	// Prevent using constructors
	Log() = default;
	~Log() = default;

	LogLevel _logLevel = LogLevel::INFO;

};