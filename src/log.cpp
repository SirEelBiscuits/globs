#include "log.h"

std::fstream Logger::s_file;
std::set<std::string> Logger::s_activeChannels;
bool Logger::s_echo = true;
bool Logger::s_logAll = false;

void Logger::log( std::string channel, std::string message) {
	if( s_activeChannels.find( channel ) != s_activeChannels.end()
		|| s_logAll
	) {
		if( s_file.is_open() )
			s_file << "[" << channel << "] " << message << std::endl;
		if( s_echo )
			std::cout << "[" << channel << "] " << message << std::endl;
	}
}

void Logger::activateChannel( std::string channel ) {
	s_activeChannels.insert( channel );
}

void Logger::deactivateChannel( std::string channel ) {
	s_activeChannels.erase( channel );
}

bool Logger::setFileName( std::string filename ) {
	if( s_file.is_open() )
		s_file.close();
	s_file.open( filename );
	return s_file.is_open();
}

void Logger::setLogAll( bool newLogAll ) {
	s_logAll = newLogAll;
}
