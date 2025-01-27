#include "Logger.h"

using namespace LoopEngine;

// MÉTHODES
Logger::Logger(const TLevel InLoggingLevel, bool InConsoleTraceActive, bool InFileTraceActive)
{
	_LoggingLevel = InLoggingLevel;
	_IsConsoleTraceActive = InConsoleTraceActive;
	_IsFileTraceActive = InFileTraceActive;
}

Logger::~Logger() // Delete
{
}

void Logger::ActivateConsoleTrace(bool InIsActive)
{
}

void Logger::SetLoggingLevel(const TLevel InLoggingLevel)
{
}

void Logger::Log(string msg, const TLevel InLoggingLevel) const
{
}

void Logger::ActivateFileTrace(bool InIsActive)
{
}

void Logger::ActivateFileTrace(bool InIsActive, const string& InFileName)
{
}

void Logger::SetFileTraceName(const string InFileTraceName)
{
}

void Logger::SetAbortLevel(const TLevel InAbortLevel)
{
}

bool Logger::TryOpenFile()
{
	return false;
}

bool Logger::TryCloseFile()
{
	return false;
}
