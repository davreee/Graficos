#include "PAGrenderer.h"
#include <stdlib.h>
#include <math.h>
#include <stdexcept>

PAGrenderer* PAGrenderer::instancia = nullptr;

PAGrenderer::PAGrenderer() :colorComponenteR(0.3), colorComponenteG(0.6), colorComponenteB(0.9), colorComponenteA(1.0), shaderProgram(nullptr) {

}

PAGrenderer::~PAGrenderer() {
	if (shaderProgram != nullptr)
		delete shaderProgram;
}

PAGrenderer* PAGrenderer::getInstancia() {
	if (!instancia) {
		instancia = new PAGrenderer();
	}

	return instancia;
}

void PAGrenderer::rellenarFondo()
{
	glClearColor(colorComponenteR, colorComponenteG, colorComponenteB, colorComponenteA);
}

void PAGrenderer::setColorBorrado(GLclampf incrementoR, GLclampf incrementoG, GLclampf incrementoB, GLclampf incrementoA)
{
	colorComponenteR = incrementoR;
	colorComponenteG = incrementoG;
	colorComponenteB = incrementoB;
	colorComponenteA = incrementoA;
}

void PAGrenderer::setViewport(GLuint orX, GLuint orY, GLsizei ancho, GLsizei alto)
{
	glViewport(orX, orY, ancho, alto);
}

void PAGrenderer::callbackScroll(double xoffset, double yoffset)
{
	if (yoffset < 0) {
		//Baja la ruedecilla
		colorComponenteR -= cambioColorAleatorio();
		colorComponenteG -= cambioColorAleatorio();
		colorComponenteB -= cambioColorAleatorio();
	}
	else if (yoffset > 0)
	{
		//Sube la ruedecilla
		colorComponenteR += cambioColorAleatorio();
		colorComponenteG += cambioColorAleatorio();
		colorComponenteB += cambioColorAleatorio();
	}

	//Truncamos las componentes que se salgan del Rango [0,1]
	//Componente R
	if (colorComponenteR < 0.0 || colorComponenteR > 1.0) {
		colorComponenteR = truncf(colorComponenteR);
	}
	//Componente G
	if (colorComponenteG < 0.0 || colorComponenteG > 1.0) {
		colorComponenteG = truncf(colorComponenteG);
	}
	//Componente B
	if (colorComponenteB < 0.0 || colorComponenteB > 1.0) {
		colorComponenteB = truncf(colorComponenteB);
	}

	//Pintamos del nuevo color
	rellenarFondo();
}

void PAGrenderer::activarZBuffer()
{
	glEnable(GL_DEPTH_TEST);
}


void PAGrenderer::addColorBorrado(GLclampf incremento) {

	//Añadimos el incremento a cada componente
	colorComponenteR += incremento;
	colorComponenteG += incremento;
	colorComponenteB += incremento;
	colorComponenteA += incremento;

	//Truncamos las componentes que se superen el valor de 1 tras hacer el incremento
	//Componente R
	if (colorComponenteR > 1.0) {
		colorComponenteR = truncf(colorComponenteR);
	}
	//Componente G
	if (colorComponenteG > 1.0) {
		colorComponenteG = truncf(colorComponenteG);
	}
	//Componente B
	if (colorComponenteB > 1.0) {
		colorComponenteB = truncf(colorComponenteB);
	}
	if (colorComponenteA > 1.0) {
		colorComponenteA = truncf(colorComponenteA);
	}//Componente A

	//Pintamos del nuevo color
	rellenarFondo();
}

void PAGrenderer::addColorBorrado(GLclampf incrementoR, GLclampf incrementoG, GLclampf incrementoB, GLclampf incrementoA) {

	//Añadimos el incremento correspondiente a cada componente
	colorComponenteR += incrementoR;
	colorComponenteG += incrementoG;
	colorComponenteB += incrementoB;
	colorComponenteA += incrementoA;

	//Truncamos las componentes que se superen el valor de 1 tras hacer el incremento
	//Componente R
	if (colorComponenteR > 1.0) {
		colorComponenteR = truncf(colorComponenteR);
	}
	//Componente G
	if (colorComponenteG > 1.0) {
		colorComponenteG = truncf(colorComponenteG);
	}
	//Componente B
	if (colorComponenteB > 1.0) {
		colorComponenteB = truncf(colorComponenteB);
	}
	if (colorComponenteA > 1.0) {
		colorComponenteA = truncf(colorComponenteA);
	}

	//Pintamos del nuevo color
	rellenarFondo();
}

void PAGrenderer::addShaderProgram(std::string nombre)
{
	//Si ya hay un shader lo eliminamos
	if (shaderProgram != nullptr) {
		delete shaderProgram;
		shaderProgram = nullptr;
	}
	//Creamos el shader
	shaderProgram = new PAGshaderProgram();
	try
	{
		shaderProgram->creaShaderProgram(nombre);

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderProgram->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}
}

void PAGrenderer::borraBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PAGrenderer::refrescaVentana()
{
	borraBuffers();
	//Como sabemos hay que activar el shader program cada vez que se va a dibujar la escena
	shaderProgram->activar();
}

float PAGrenderer::cambioColorAleatorio() {
	return  ((rand() % 5) + 1) * 0.01;
}