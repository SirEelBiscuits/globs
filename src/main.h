#include "gargamel/gargamel.h"

enum ArgNames {
	Unknown,
	Help,
	LogFile,
	EchoLog,
	LogChannel,
	LogAll,
	ScreenWidth,
	ScreenHeight,
	FullScreen,
};
START_ARGS(Arguments)
	DESCRIBE_ARG(Unknown, 		'\0', 	nullptr,	NoArg,		"Usage Instructions:\n")
	DESCRIBE_ARG(Help, 		'h', 	"help", 	NoArg,		"\tPrint help text\n")
	DESCRIBE_ARG(LogFile, 		'\0', 	"log", 		RequiredArg,	"\tSpecify log file\n")
	DESCRIBE_ARG(EchoLog,		'e',	"echo", 	NoArg,		"\tEcho log to console\n")
	DESCRIBE_ARG(LogAll,		'v',	"verbose", 	NoArg,		"\tLog all messages, regardless of channel\n")
	DESCRIBE_ARG_ARRAY(LogChannel, 		"log-channel", 			"\tTurn on logging channel\n")
	DESCRIBE_ARG_DEFAULT(ScreenWidth,	'w',	"width", 	RequiredArg,	"800", "\tSet the width of the window\n")
	DESCRIBE_ARG_DEFAULT(ScreenHeight,	'h',	"height", 	RequiredArg,	"600", "\tSet the height of the window\n")
	DESCRIBE_ARG(FullScreen,	'f',	"full-screen", 	NoArg,		"\tStart in full screen mode\n")
END_ARGS

void Init(int argc, char* argv[]);
int main(int argc, char* argv[]);
