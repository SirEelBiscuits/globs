#include "log.h"

std::fstream Logger::s_file;
std::set<std::string> Logger::s_activeChannels;

void Logger::log( std::string channel, std::string message) {
	if( s_activeChannels.find( channel ) != s_activeChannels.end() )
		s_file << "[" << channel << "] " << message << std::endl;
}

void Logger::activateChannel( std::string channel ) {
	s_activeChannels.insert( channel );
}

void Logger::deactivateChannel( std::string channel ) {
	s_activeChannels.erase( channel );
}

bool Logger::initLogger( std::string filename ) {
	s_file.open( filename );
	return s_file.is_open();
}

