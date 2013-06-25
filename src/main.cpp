#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glfw.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>


#include "shader.h"
#include "version.inc"
#include "arrays.h"
#include "log.h"
#include "gargamel/gargamel.h"

#include <IL/il.h>

enum ArgNames {
	Unknown,
	Help,
	LogFile,
	LogChannel,
};
START_ARGS(Arguments)
	DESCRIBE_ARG(Unknown, 		'\0', 	nullptr, NoArg, 	"Usage Instructions:\n")
	DESCRIBE_ARG(Help, 		'h', 	"help", NoArg, 		"\tPrint help text\n")
	DESCRIBE_ARG(LogFile, 		'\0', 	"log", 	RequiredArg, 	"\tSpecify log file\n")
	DESCRIBE_ARG_ARRAY(LogChannel, 		"log-channel", 		"\tTurn on logging channel\n")
END_ARGS

int main(int argc, char* argv[]) {
	bool argProc = Gargamel::Process(Arguments, argc, argv);
	if( !argProc )
		std::cout << "Arguments iffy " << argc << std::endl;

	if( Gargamel::ArgumentSet[Help].isArgumentPresent )
	{
		Gargamel::ShowUsage();
		return EXIT_SUCCESS;
	}
	if( Gargamel::ArgumentSet[LogFile].isArgumentPresent )
	{
		std::cout << "filename set to " << Gargamel::ArgumentSet[LogFile].argumentValue << std::endl;
		Logger::setFileName( Gargamel::ArgumentSet[LogFile].argumentValue );
	}
	for( auto s : *(Gargamel::ArgumentSet[LogChannel].argumentArray) )
	{
		std::cout << "Channel activated: " << s << std::endl;
		Logger::activateChannel(s);
	}

	Logger::log( "INFO", "Starting version" VERSION );
	if( !glfwInit() ) {
		Logger::log( "ERR", "glfwInit failed" );
		exit(-1);
	}

	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);


	if( !glfwOpenWindow(800,600,8,8,8,0,0,0,GLFW_WINDOW) ) {
		glfwTerminate();
		Logger::log( "ERR", "Failed to open window" );
		exit(-1);
	}

	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK) {
		glfwTerminate();
		exit(-1);
	}

	ilInit();

	std::vector<GLfloat> verts = {
		0.,	0.,
		.5,	0.,
		.5,	.5,

		0.,	0.,
		0.,	.5,
		-.5,	.5,

		0.,	0.,
		-.5,	0.,
		-.5,	-.5,

		0.,	0.,
		0.,	-.5,
		.5,	-.5
	};

	std::vector<GLfloat> colors = {
		1.0,	1.0,	1.0,
		1.0,	1.0,	0.3,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	0.3,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		1.0,	1.0,	1.0,
		0.5,	1.0,	1.0
	};

	std::vector<GLfloat> interleaved;

	Interleave(verts, 2, colors, 3, interleaved);

	GLuint vbo; glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, interleaved.size() * sizeof(GLfloat) , interleaved.data(), GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	BindParameter(GetBasicShader(), "position", 2, GL_FLOAT, 5 * sizeof(GLfloat), 0);
	BindParameter(GetBasicShader(), "color", 3, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat)*2));

	glClearColor(1.,0.,0.,1.);
	while(glfwGetWindowParam(GLFW_OPENED)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		glfwSwapBuffers();
	}
	glfwTerminate();
	return 0;
}
