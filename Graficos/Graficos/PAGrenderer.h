#include <GL\glew.h>
#include <GL\GL.h>
#include <string>
#include "PAGshaderProgram.h"
class PAGrenderer
{
private:
	static PAGrenderer* instancia;
	PAGrenderer();
	//Variables que almacenan el color de la escena
	float colorComponenteR;
	float colorComponenteG;
	float colorComponenteB;
	float colorComponenteA;
	//Función que genera el cambio que tendrá la componente aleatoriamente en el rango [0.01, 0.05]
	float cambioColorAleatorio();
	PAGshaderProgram* shaderProgram;
public:
	static PAGrenderer* getInstancia();
	void rellenarFondo();
	void addColorBorrado(GLclampf incremento);
	void addColorBorrado(GLclampf incrementoR, GLclampf incrementoG, GLclampf incrementoB, GLclampf incrementoA);
	void addShaderProgram(std::string nombre);
	void borraBuffers();
	void refrescaVentana();
	void setColorBorrado(GLclampf incrementoR, GLclampf incrementoG, GLclampf incrementoB, GLclampf incrementoA);
	void setViewport(GLuint orX, GLuint orY, GLsizei ancho, GLsizei alto);
	void callbackScroll(double xoffset, double yoffset);
	void activarZBuffer();
	~PAGrenderer();
};

