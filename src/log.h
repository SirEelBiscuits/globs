#pragma once

#include <iostream>
#include <set>
#include <string>
#include <fstream>

class Logger {
private:
	static std::fstream s_file;
	static std::set<std::string> s_activeChannels;
	static bool s_echo;
	static bool s_logAll;

public:
	static bool setFileName(std::string filename);

	static void log(std::string channel, std::string message);
	static void activateChannel(std::string channel);
	static void deactivateChannel(std::string channel);
	static void echo(bool toEcho) { s_echo = toEcho; }
	static void setLogAll(bool newLogAll);
};
