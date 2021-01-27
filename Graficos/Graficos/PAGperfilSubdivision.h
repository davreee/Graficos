#pragma once
#include <vector>
#include <GL\glew.h>
#include <GL\GL.h>
#include <glm.hpp>
#include "PAGtextura.h"
#include "PAGvalores.h"
class PAGperfilSubdivision
{
private:
	std::vector<glm::vec2> puntosPerfil;
	bool valido;
	void comprobarValidez();
	glm::vec2 sumarPunto(glm::vec2 punto, float valor);
	glm::vec2 multiplicarPunto(glm::vec2 punto, float valor);
public:
	PAGperfilSubdivision(std::vector<glm::vec2> puntos);
	PAGperfilSubdivision subdivide(int numVeces);
	bool perfilValido();
	std::vector<glm::vec2> getPuntos();
};

