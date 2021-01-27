#pragma once
#include <GL\glew.h>
#include <GL\GL.h>
#include <string>
#include <vector>
#include "lodepng.h"
class PAGnormalMap
{
private:
	GLuint identificador;
	GLuint altura;
	GLuint anchura;
	std::string nombreNormalMap;
	std::vector<unsigned char> imagen;
	bool listo;
	void cargarNormalMap();
	void generarNormalMap();
public:
	PAGnormalMap();
	PAGnormalMap(std::string nombreMap, GLuint alto, GLuint ancho);
	void activarNormalMap();
};

