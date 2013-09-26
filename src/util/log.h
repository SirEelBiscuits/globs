#pragma once

#include <iostream>
#include <set>
#include <string>
#include <fstream>

#include <cstdio>

/**
 * General way to access logging commands.
 *
 * This automatically fills out the file and line, for ease of tracking down
 * where messages came from
 */
#define LOG_MSG(Channel, ...) Logger::log(Channel, __FILE__, \
		__LINE__, __VA_ARGS__)
/**
 * As LOG_MSG, but with file and line specified
 *
 * This is for use in logging utility functions, so that the original
 * caller's file and line can be output instead.
 */
#define LOG_MSG_LOC(Channel, file, line, ...) Logger::log(Channel, file, \
		line, __VA_ARGS__)

/**
 * Channel based logging class.
 *
 * Logging class. Uses channels, for ease of separation. Can output to a
 *  file, which can then be checked with tail -f file | grep "channel", as
 *  well as echoed to stdout. Individual channels may be turned on and off
 *  at any time.
 */
class Logger {
public:
	/**
	 * Set the log file to write to.
	 *
	 * All active channels will be written to this file. Only one file
	 * may be used at once. If echo has been set, the file will still
	 * get written to, as well as stdout.
	 */
	static bool setFileName(std::string filename);

	static void activateChannel(std::string channel);
	static void deactivateChannel(std::string channel);

	/**
	 * Causes log messages to be written to the screen.
	 *
	 * Only active channels will be written to the screen, and if a log
	 * file is specified, messages will still be written there as well.
	 */
	static void echo(bool toEcho);

	/**
	 * tell the logger to log all cahnels, active or not.
	 */
	static void setLogAll(bool newLogAll);

	/**
	 * The main log function
	 *
	 * This will check the list of active channels for the channel
	 * specified, and if it is present, log the message to the log file
	 * if it has been specified, and to stdout if echo is turned on.
	 *
	 * \param channel The channel the message is being sent to
	 *
	 * \param file The file the message originated at.
	 *
	 * \param line The line the message originated at.
	 *
	 * \param format This will be used as the format for the printf
	 * internally, check your compiler documentation for its exact use.
	 *
	 * \param ... These additional arguments will also be passed to the
	 * printf.
	 *
	 */
	static void log(
		std::string channel,
	       	char const* file,
		int line,
		char const* format,
	       	...
	);

private:
	static FILE* s_file;
	static std::set<std::string> s_activeChannels;
	static bool s_echo;
	static bool s_logAll;
};
