#pragma once
#include <GL\glew.h>
#include <GL\GL.h>
#include <string>
#include <vector>
#include "lodepng.h"
class PAGtextura
{
private:
	GLuint identificador;
	GLuint altura;
	GLuint anchura;
	std::string nombreTextura;
	std::vector<unsigned char> imagen;
	bool listo;
	void cargarTextura();
	void generarTextura();
public:
	PAGtextura(std::string nombreArchivo, GLuint alto, GLuint ancho);
	void activarTextura();
};

