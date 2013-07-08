#include "gargamel/gargamel.h"

enum ArgNames {
	Unknown,
	Help,
	LogFile,
	EchoLog,
	LogChannel,
	LogAll,
};
START_ARGS(Arguments)
	DESCRIBE_ARG(Unknown, 		'\0', 	nullptr, NoArg, 	"Usage Instructions:\n")
	DESCRIBE_ARG(Help, 		'h', 	"help", NoArg, 		"\tPrint help text\n")
	DESCRIBE_ARG(LogFile, 		'\0', 	"log", 	RequiredArg, 	"\tSpecify log file\n")
	DESCRIBE_ARG(EchoLog,		'e',	"echo", NoArg,		"\tEcho log to console\n")
	DESCRIBE_ARG_ARRAY(LogChannel, 		"log-channel", 		"\tTurn on logging channel\n")
	DESCRIBE_ARG(LogAll,		'v',	"verbose", NoArg,	"\tLog all messages, regardless of channel\n")
END_ARGS

void Init(int argc, char* argv[]);
int main(int argc, char* argv[]);
