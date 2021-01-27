#include <GL\glew.h>
#include <GL\GL.h>
#include <glm.hpp>
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
	void setUniform(std::string nombre, GLint valor);
	void setUniform(std::string nombre, GLfloat valor);
	void setUniform(std::string nombre, glm::vec3 valor);
	void setUniform(std::string nombre, glm::mat4 valor);
};

