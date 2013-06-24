#include <iostream>
#include <set>
#include <string>
#include <fstream>

class Logger {
private:
	static std::fstream s_file;
	static std::set<std::string> s_activeChannels;

public:
	static void setFileName( std::string filename );
	static bool initLogger( std::string filename );

	static void log( std::string channel, std::string message);
	static void activateChannel( std::string channel );
	static void deactivateChannel( std::string channel );
};
