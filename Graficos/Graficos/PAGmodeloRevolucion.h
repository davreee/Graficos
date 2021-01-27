#pragma once
#include "PAGvao.h"
#include <vector>
#include <GL\glew.h>
#include <GL\GL.h>
#include "PAGtextura.h"
#include "PAGvalores.h"
#include "PAGperfilSubdivision.h"
#include "PAGinstancia.h"
#include "PAGmaterial.h"
class PAGmodeloRevolucion
{
private:
	PAGperfilSubdivision perfil;
	PAGvao cuerpo;
	PAGvao tapaSuperior;
	PAGvao tapaInferior;
	PAGtextura* textura;
	PAGinstancia instancia;
	PAGmaterial* material;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normales;
	std::vector<glm::vec2> textCoor;
	std::vector<unsigned int> indices;
	glm::vec2 puntoTapaInferior;
	glm::vec2 puntoTapaSuperior;
	int numPuntos;
	int numSubdivisiones;
	bool hayTapaSuperior;
	bool hayTapaInferior;
	void algoritmoGeneracionPuntos(std::vector<glm::vec2>& puntosPerfil, unsigned int subdivisionesPerfil, unsigned int subdivisionesRadial);
	void algoritmoGeneracionMalla(unsigned int subdivisionesRadial);
	void generarVaos();

public:
	PAGmodeloRevolucion(std::vector<glm::vec2> puntos, unsigned int subdivisionesPerfil, unsigned int subdivisionesRadial, int idModelo);
	void pintar(PAGvalores::PAGpartesRevolucion parte);
	void trasladar(glm::vec3 traslacion);
	glm::mat4 obtenerInstancia();
	bool esValido();
	bool tiene(PAGvalores::PAGpartesRevolucion parte);
};

