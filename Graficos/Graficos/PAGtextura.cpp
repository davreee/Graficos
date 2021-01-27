#include "PAGtextura.h"
#include "PAGtextura.h"
#include <stdexcept>

PAGtextura::PAGtextura(std::string nombreArchivo, GLuint alto, GLuint ancho) :
	nombreTextura(nombreArchivo),
	imagen(),
	altura(alto),
	anchura(ancho),
	listo(false)
{

}

void PAGtextura::cargarTextura()
{
	/** Carga un png de disco https://lodev.org/lodepng/ */
	unsigned error = lodepng::decode(imagen, anchura, altura, nombreTextura);
	if (error)
	{
		std::string message = nombreTextura + " can not be loaded";
		throw std::runtime_error(message);
	}
	// La textura se carga del revés, así que vamos a darle la vuelta
	unsigned char* imgPtr = &imagen[0];
	int numColorComponents = 4;
	int wInc = anchura * 4; //width in char
	unsigned char* top = nullptr;
	unsigned char* bot = nullptr;
	unsigned char temp = 0;
	for (int i = 0; i < altura / 2; i++)
	{
		top = imgPtr + i * wInc;
		bot = imgPtr + (altura - i - 1) * wInc;
		for (int j = 0; j < wInc; j++)
		{
			temp = *top;
			*top = *bot;
			*bot = temp;
			++top;
			++bot;
		}
	}

}

void PAGtextura::activarTextura()
{
	if (!listo) {
		generarTextura();
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, identificador);
}

void PAGtextura::generarTextura()
{

	glGenTextures(1, &identificador);
	glBindTexture(GL_TEXTURE_2D, identificador);
	cargarTextura();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, anchura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)imagen.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	listo = true;
}
