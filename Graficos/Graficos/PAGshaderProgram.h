#include <GL\glew.h>
#include <GL\GL.h>
#include <string>
class PAGshaderProgram
{
private:
	GLuint identificador;
	bool enlazado;
	std::string mensajeGLSL;
	GLuint compilar(std::string nombreArchivo, GLenum tipoShader);
	void enlazar(std::string nombreBase);
public:
	PAGshaderProgram();
	void activar();
	GLuint creaShaderProgram(std::string nombreBase);
	std::string getMensajeGLSL();
};

