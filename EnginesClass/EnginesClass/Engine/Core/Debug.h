#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>

enum class MessageType : unsigned short { // unsigned short uses 2 bytes
	TYPE_NONE,
	TYPE_FATAL_ERROR,
	TYPE_ERROR,
	TYPE_WARNING,
	TYPE_TRACE,
	TYPE_INFO
};

class Debug // Log Manager
{
public:
	Debug() = delete; // making it fully static class, fully deleting constructor, NO INTANCES

	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	static void DebugInit();
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:
	static void Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_);
	static MessageType currentSev; // Status?
	static std::string outputName;
};
#endif