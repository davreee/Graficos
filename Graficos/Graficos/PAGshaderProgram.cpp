#include "PAGshaderProgram.h"
#include <fstream>
#include <stdexcept>
PAGshaderProgram::PAGshaderProgram() :identificador(0), enlazado(false), mensajeGLSL("")
{
}

GLuint PAGshaderProgram::compilar(std::string nombreArchivo, GLenum tipoShader)
{
	//Creamos el Shader
	GLuint identificadorShader;
	identificadorShader = glCreateShader(tipoShader);
	//Leemos el archivo fuente, si no existe, lanzamos una excepción.
	std::string stringShader;
	std::string linea;
	std::ifstream fe(nombreArchivo);
	if (!fe) {
		throw std::invalid_argument("creaShaderProgram: error. No existe el archivo "
			+ nombreArchivo);
	}
	while (getline(fe, linea))
		stringShader += "\n" + linea;
	fe.close();
	//Compilamos el shader
	const GLchar* fuenteShader = stringShader.c_str();
	glShaderSource(identificadorShader, 1, &fuenteShader, nullptr);
	glCompileShader(identificadorShader);
	//Comprobamos el estado de la compilación
	GLint resultadoCompilacion = 0;
	glGetShaderiv(identificadorShader, GL_COMPILE_STATUS, &resultadoCompilacion);
	//Tratamos el estado fallido de la compilación
	if (resultadoCompilacion == GL_FALSE)
	{
		GLint tamMensaje = 0;
		mensajeGLSL = "";
		glGetShaderiv(identificadorShader, GL_INFO_LOG_LENGTH, &tamMensaje);
		if (tamMensaje > 0)
		{
			GLchar* textoMensaje = new GLchar[tamMensaje];
			GLint numCaracteres = 0;
			glGetShaderInfoLog(identificadorShader, tamMensaje, &numCaracteres, textoMensaje);
			mensajeGLSL = textoMensaje;
		}
		throw std::runtime_error("creaShaderProgram: error al compilar programa el programa "
			+ nombreArchivo);
	}

	//Si el proceso es correcto, devolvemos el identificador del shader.
	return identificadorShader;
}

void PAGshaderProgram::enlazar(std::string nombreBase)
{
	glLinkProgram(identificador);
	//Comprobamos el estado del enlazado
	GLint resultadoEnlazado = 0;
	glGetProgramiv(identificador, GL_LINK_STATUS, &resultadoEnlazado);

	if (resultadoEnlazado == GL_FALSE)
	{
		GLint tamMensaje = 0;
		mensajeGLSL = "";
		glGetProgramiv(identificador, GL_INFO_LOG_LENGTH, &tamMensaje);

		if (tamMensaje > 0)
		{
			GLchar* textoMensaje = new GLchar[tamMensaje];
			GLint numCaracteres = 0;
			glGetProgramInfoLog(identificador, tamMensaje, &numCaracteres, textoMensaje);
			mensajeGLSL = textoMensaje;
		}
		throw std::runtime_error("creaShaderProgram: error al enlazar el programa "
			+ nombreBase);
	}

	enlazado = true;
}

void PAGshaderProgram::activar()
{
	glUseProgram(identificador);
}

GLuint PAGshaderProgram::creaShaderProgram(std::string nombreBase)
{
	//Creamos el shader program
	identificador = glCreateProgram();

	try {
		//Creamosel vertex shader y lo compilamos
		std::string vertexShader = nombreBase + "-vert.glsl";
		GLuint identificadorVertex = compilar(vertexShader, GL_VERTEX_SHADER);
		//Creamosel fragment shader y lo compilamos
		std::string fragmentShader = nombreBase + "-frag.glsl";
		GLuint identificadorFragment = compilar(fragmentShader, GL_FRAGMENT_SHADER);
		//Añadimos los shader
		glAttachShader(identificador, identificadorVertex);
		glAttachShader(identificador, identificadorFragment);
		//Enlazamos los shaders
		enlazar(nombreBase);
		//Eliminamos los shaders
		glDeleteShader(identificadorVertex);
		glDeleteShader(identificadorFragment);
		//Activamos el shader program y devolvemos su identificador
		activar();
		return identificador;
	}
	catch (std::runtime_error e) {
		throw e;
	}
	catch (std::invalid_argument e) {
		throw e;
	}


}

std::string PAGshaderProgram::getMensajeGLSL()
{
	return mensajeGLSL;
}

void PAGshaderProgram::setUniform(std::string nombre, GLint valor)
{
	GLint location = glGetUniformLocation(identificador, nombre.c_str());

	if (location < 0) {
		throw std::out_of_range("Error al localizar la variable: " + nombre);
	}
	glUniform1i(location, valor);
}

void PAGshaderProgram::setUniform(std::string nombre, GLfloat valor)
{
	GLint location = glGetUniformLocation(identificador, nombre.c_str());

	if (location < 0) {
		throw std::out_of_range("Error al localizar la variable: " + nombre);
	}

	glUniform1f(location, valor);
}

void PAGshaderProgram::setUniform(std::string nombre, glm::vec3 valor)
{
	GLint location = glGetUniformLocation(identificador, nombre.c_str());
	
	if (location < 0) {
		throw std::out_of_range("Error al localizar la variable: " + nombre);
	}

	glUniform3fv(location, 1, &valor[0]);
}

void PAGshaderProgram::setUniform(std::string nombre, glm::mat4 valor)
{
	GLint location = glGetUniformLocation(identificador, nombre.c_str());

	if (location < 0) {
		throw std::out_of_range("Error al localizar la variable: " + nombre);
	}

	glUniformMatrix4fv(location, 1, false, &valor[0][0]);
}
