#pragma once

#include <iostream>
#include <set>
#include <string>
#include <fstream>

#include <cstdio>

/*
 * Logging class. Uses channels, for ease of separation. Can output to a
 *  file, which can then be checked with tail -f file | grep "channel", as
 *  well as echoed to stdout. Individual channels may be turned on and off
 *  at any time.
 */
#define LOG_MSG(Channel, ...) Logger::log(Channel, __FILE__, \
		__LINE__, __VA_ARGS__)
#define LOG_MSG_LOC(Channel, file, line, ...) Logger::log(Channel, file, \
		line, __VA_ARGS__)
class Logger {
private:
	static FILE* s_file;
	static std::set<std::string> s_activeChannels;
	static bool s_echo;
	static bool s_logAll;

public:
	static bool setFileName(std::string filename);

	static void log(
		std::string channel,
	       	char const* file,
		int line,
		char const* format,
	       	...
	);
	static void activateChannel(std::string channel);
	static void deactivateChannel(std::string channel);
	static void echo(bool toEcho) { s_echo = toEcho; }
	static void setLogAll(bool newLogAll);
};
