#include "PAGperfilSubdivision.h"


PAGperfilSubdivision::PAGperfilSubdivision(std::vector<glm::vec2> puntos) :
	puntosPerfil(puntos),
	valido()
{
	comprobarValidez();
}

void PAGperfilSubdivision::comprobarValidez()
{
	bool bandera = true;

	if (puntosPerfil.size() <= 1) {
		bandera = false;
	}


	if (puntosPerfil.size() == 2 && puntosPerfil.at(0).x == 0.0 && puntosPerfil.at(1).x == 0.0)
		bandera = false;

	if (puntosPerfil.size() == 3 && puntosPerfil.at(0).x == 0.0 && puntosPerfil.at(2).x == 0.0)
		bandera = false;

	int contador = 0;
	while (bandera && contador < puntosPerfil.size()) {
		if (puntosPerfil.at(contador).x < 0.0)
			bandera = false;
		if (puntosPerfil.at(contador).x == 0 && contador != 0 && contador != puntosPerfil.size() - 1)
			bandera = false;
		contador++;
	}

	valido = bandera;
}

PAGperfilSubdivision PAGperfilSubdivision::subdivide(int numVeces)
{
	std::vector<glm::vec2> puntosAux;
	std::vector<glm::vec2> puntos = puntosPerfil;
	for (int i = 0; i < numVeces; i++) {

		puntosAux.push_back(puntos.at(0));
		for (int j = 1; j <= puntos.size() - 2; j++)
		{
			glm::vec2 primerAux(puntos.at(j - 1) + puntos.at(j));
			puntosAux.push_back(multiplicarPunto(primerAux, 0.5));
			glm::vec2 segundoAux(multiplicarPunto(puntos.at(j), 0.75) + multiplicarPunto(puntos.at(j - 1), 0.125) + multiplicarPunto(puntos.at(j + 1), 0.125));
			puntosAux.push_back(segundoAux);
		}
		glm::vec2 tercerAux((puntos.at(puntos.size() - 2) + puntos.at(puntos.size() - 1)));
		puntosAux.push_back(multiplicarPunto(tercerAux, 0.5));
		puntosAux.push_back(puntos.at(puntos.size() - 1));

		puntos.clear();
		puntos = puntosAux;
	}

	return PAGperfilSubdivision(puntos);
}

bool PAGperfilSubdivision::perfilValido()
{
	return valido;
}

glm::vec2 PAGperfilSubdivision::sumarPunto(glm::vec2 punto, float valor)
{
	return glm::vec2(punto.x + valor, punto.y + valor);
}

glm::vec2 PAGperfilSubdivision::multiplicarPunto(glm::vec2 punto, float valor)
{
	return glm::vec2(punto.x * valor, punto.y * valor);
}

std::vector<glm::vec2> PAGperfilSubdivision::getPuntos()
{
	return puntosPerfil;
}
