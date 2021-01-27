#pragma once
#include <GL\glew.h>
#include <gl\GL.h>
#include <glm.hpp>
#include "PAGvalores.h"
class PAGfuenteLuz
{
private:
	PAGvalores::PAGTipoLuz tipoLuz;
	glm::vec3 intensidadAmbiente;
	glm::vec3 intensidadDifusa;
	glm::vec3 intensidadEspecular;
	glm::vec3 posicion;
	glm::vec3 direccion;
	GLfloat apertura;
public:
	PAGfuenteLuz(glm::vec3 iAmbiente);
	PAGfuenteLuz(PAGvalores::PAGTipoLuz tipo, glm::vec3 posDir, glm::vec3 iDifusa, glm::vec3 iEspecular);
	PAGfuenteLuz(glm::vec3 pos, glm::vec3 dir, glm::vec3 iDifusa, glm::vec3 iEspecular, GLfloat anguloApertura);
	glm::vec3 getIntensidadAmbiente();
	glm::vec3 getIntensidadDifusa();
	glm::vec3 getIntensidadEspecular();
	glm::vec3 getPosicion();
	glm::vec3 getDireccion();
	GLfloat getApertura();
};

