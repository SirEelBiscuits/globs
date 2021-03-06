#include "../util/log.h"

#include <cstdarg>

FILE* Logger::s_file = nullptr;
std::set<std::string> Logger::s_activeChannels;
bool Logger::s_echo = true;
bool Logger::s_logAll = false;

void Logger::log(
	std::string channel,
	char const* file,
	int line,
	char const* format,
	...
) {
	va_list ap;
	va_start(ap, format);

	if(s_activeChannels.find(channel) != s_activeChannels.end()
		|| s_logAll
	) {
		if(s_file != nullptr)
		{
			fprintf(s_file, "[%s] %s:%d:\t",
				channel.c_str(),
				file,
				line
			);
			vfprintf(s_file, format, ap);
			fprintf(s_file, "\n");
			fflush(s_file);
		}
		if(s_echo)
		{
			printf("[%s] %s:%d:\t",
				channel.c_str(),
				file,
				line
			);
			vprintf(format, ap);
			printf("\n");
			fflush(stdout);
		}
	}
}

void Logger::activateChannel(std::string channel) {
	s_activeChannels.insert(channel);
}

void Logger::deactivateChannel(std::string channel) {
	s_activeChannels.erase(channel);
}

bool Logger::setFileName(std::string filename) {
	if(s_file)
		fclose(s_file);
	s_file = fopen(filename.c_str(), "w");
	return s_file != nullptr;
}

void Logger::echo(bool toEcho) {
	s_echo = toEcho;
}

void Logger::setLogAll(bool newLogAll) {
	s_logAll = newLogAll;
}
