#include "PAGmodeloRevolucion.h"
#include <iostream>
void PAGmodeloRevolucion::algoritmoGeneracionPuntos(std::vector<glm::vec2>& puntosPerfil, unsigned int subdivisionesPerfil, unsigned int subdivisionesRadial)
{
	glm::vec2 puntoAnterior;
	glm::vec2 puntoActual;

	float longitudAcumulada = 0.0;
	float longitudTotal = 0.0;

	float delta = 360 / subdivisionesRadial;
	float u;
	float v;

	if (subdivisionesPerfil > 0) {
		perfil = perfil.subdivide(subdivisionesPerfil);
	}

	if (perfil.perfilValido()) {



		std::vector<glm::vec2> puntos = perfil.getPuntos();
		if (puntos.at(0).x == 0) {
			puntoTapaInferior = puntos.at(0);
			puntos.erase(puntos.begin());
			hayTapaInferior = true;
		}
		if (puntos.at(puntos.size() - 1).x == 0) {
			puntoTapaSuperior = puntos.at(puntos.size() - 1);
			puntos.erase(puntos.end() - 1);
			hayTapaSuperior = true;
		}
		numPuntos = puntos.size();

		std::vector<glm::vec2> normalesOriginales;
		normalesOriginales.push_back(glm::vec2(1, 0));

		for (int i = 1; i < numPuntos - 1; i++)
		{
			glm::vec2 normalSiguiente(glm::normalize(puntos.at(i + 1) - puntos.at(i)));
			normalSiguiente = glm::vec2(normalSiguiente.y, -normalSiguiente.x);
			glm::vec2 normalAnterior(glm::normalize(puntos.at(i - 1) - puntos.at(i)));
			normalAnterior = glm::vec2(normalAnterior.y, -normalAnterior.x);
			glm::vec2 normalNueva = normalSiguiente - normalAnterior;
			normalesOriginales.push_back(glm::vec2(normalNueva.x * 0.5, normalNueva.y * 0.5));
		}
		normalesOriginales.push_back(glm::vec2(1, 0));

		for (int i = 1; i <= puntos.size() - 1; i++)
		{
			longitudTotal += glm::distance(puntos.at(i), puntos.at(i - 1));
		}



		for (int i = 0; i < puntos.size(); i++) {
			if (i == 0) {
				v = 0.0;
			}
			else {
				longitudAcumulada += glm::distance(puntos.at(i), puntoAnterior);
				v = longitudAcumulada / longitudTotal;
			}
			puntoAnterior = puntos.at(i);
			glm::vec2 normalOriginal = normalesOriginales.at(i);
			for (int j = 0; j <= subdivisionesRadial; j++)
			{
				float angulo = delta * j;
				angulo = glm::radians(angulo);
				glm::vec3 puntoNuevo(puntos.at(i).x * cos(angulo), puntos.at(i).y, -puntos.at(i).x * sin(angulo));
				glm::vec3 normalNueva(normalOriginal.x * puntos.at(i).x * cos(angulo), normalOriginal.y * puntos.at(i).y, -normalOriginal.x * puntos.at(i).x * sin(angulo));
				normalNueva = glm::normalize(normalNueva);
				vertices.push_back(puntoNuevo);
				normales.push_back(normalNueva);
				float u = j * (1.0 / subdivisionesRadial);
				cuerpo.addTextCoor(glm::vec2(u, v));
			}
		}
	}



}

void PAGmodeloRevolucion::algoritmoGeneracionMalla(unsigned int subdivisionesRadial)
{
	for (int s = 0; s < subdivisionesRadial; s++)
	{
		for (int i = 0; i < numPuntos; i++)
		{
			indices.push_back((i * (subdivisionesRadial + 1)) + s);
			indices.push_back((i * (subdivisionesRadial + 1)) + (s + 1));
		}
		indices.push_back(0xFFFF);
	}
}

void PAGmodeloRevolucion::generarVaos()
{
	for (glm::vec3 vertice : vertices) {
		cuerpo.addVertice(vertice);
	}

	for (glm::vec3 normal : normales) {
		cuerpo.addNormal(normal);
	}

	for (unsigned int indice : indices) {
		cuerpo.addIndice(GL_TRIANGLE_STRIP, indice);
	}


	tapaInferior.addVertice(glm::vec3(puntoTapaInferior.x, puntoTapaInferior.y, 0));
	tapaInferior.addNormal(glm::vec3(0, -1, 0));

	for (int i = 0; i < numSubdivisiones; i++) {
		tapaInferior.addVertice(vertices.at(i));
		tapaInferior.addNormal(glm::vec3(0, -1, 0));

	}


	for (int n = 2; n <= numSubdivisiones; ++n) {
		tapaInferior.addIndice(GL_TRIANGLE_FAN, 0);
		tapaInferior.addIndice(GL_TRIANGLE_FAN, n - 1);
		tapaInferior.addIndice(GL_TRIANGLE_FAN, n);
	}
	tapaInferior.addIndice(GL_TRIANGLE_FAN, 0);
	tapaInferior.addIndice(GL_TRIANGLE_FAN, numSubdivisiones);
	tapaInferior.addIndice(GL_TRIANGLE_FAN, 1);

	tapaInferior.addIndice(GL_TRIANGLE_FAN, 0xFFFF);


	for (int i = vertices.size() - numSubdivisiones; i < vertices.size(); i++) {
		tapaSuperior.addVertice(vertices.at(i));
		tapaSuperior.addNormal(glm::vec3(0, 1, 0));
	}
	tapaSuperior.addVertice(glm::vec3(puntoTapaSuperior.x, puntoTapaSuperior.y, 0));
	tapaSuperior.addNormal(glm::vec3(0, 1, 0));

	for (int n = 2; n <= numSubdivisiones; ++n) {
		tapaSuperior.addIndice(GL_TRIANGLE_FAN, n - 1);
		tapaSuperior.addIndice(GL_TRIANGLE_FAN, n);
		tapaSuperior.addIndice(GL_TRIANGLE_FAN, numSubdivisiones);
	}

	tapaSuperior.addIndice(GL_TRIANGLE_FAN, numSubdivisiones);
	tapaSuperior.addIndice(GL_TRIANGLE_FAN, numSubdivisiones - 1);
	tapaSuperior.addIndice(GL_TRIANGLE_FAN, numSubdivisiones - 2);
	tapaSuperior.addIndice(GL_TRIANGLE_FAN, 0xFFFF);

}
															
PAGmodeloRevolucion::PAGmodeloRevolucion(std::vector<glm::vec2> puntos, unsigned int subdivisionesPerfil, unsigned int subdivisionesRadial, int idModelo) :
	cuerpo(),
	tapaSuperior(),
	tapaInferior(),
	vertices(),
	indices(),
	numPuntos(puntos.size()),
	numSubdivisiones(subdivisionesRadial),
	textura(nullptr),
	perfil(puntos),
	material(nullptr)
{
	if (idModelo == 0)
		textura = new PAGtextura("lata.png", 1400, 700);
	if (idModelo == 1)
		textura = new PAGtextura("modelorevolucion.png", 512, 512);
	material = new PAGmaterial(glm::vec3(1.0, .5, .31), glm::vec3(.5, .5, .31), glm::vec3(1, 1, 1), 250);

	algoritmoGeneracionPuntos(puntos, subdivisionesPerfil, subdivisionesRadial);
	if (perfil.perfilValido()) {
		algoritmoGeneracionMalla(subdivisionesRadial);
		generarVaos();
	}
}

void PAGmodeloRevolucion::pintar(PAGvalores::PAGpartesRevolucion parte)
{
	switch (parte)
	{
	case PAGvalores::PAG_CUERPO:
		if (!cuerpo.listoParaDibujar()) {
			cuerpo.generaArray();
		}

		//Lo activamos y lo pintamos
		cuerpo.activaArray(GL_TRIANGLE_STRIP);
		textura->activarTextura();
		cuerpo.pintaArray(GL_TRIANGLE_STRIP);
		break;
	case PAGvalores::PAG_TAPA_SUP:
		if (hayTapaSuperior) {

			if (!tapaSuperior.listoParaDibujar()) {
				tapaSuperior.generaArray();
			}
			tapaSuperior.activaArray(GL_TRIANGLE_FAN);
			tapaSuperior.pintaArray(GL_TRIANGLE_FAN);

		}
		break;
	case PAGvalores::PAG_TAPA_INF:
		if (hayTapaInferior) {

			if (!tapaInferior.listoParaDibujar()) {
				tapaInferior.generaArray();
			}
			tapaInferior.activaArray(GL_TRIANGLE_FAN);
			tapaInferior.pintaArray(GL_TRIANGLE_FAN);
		}
		break;
	default:
		break;
	}

}

void PAGmodeloRevolucion::trasladar(glm::vec3 traslacion)
{
	instancia.trasladar(traslacion);
}

glm::mat4 PAGmodeloRevolucion::obtenerInstancia()
{
	return instancia.matrizModelado(glm::vec3(0, 0, 0));
}

bool PAGmodeloRevolucion::esValido()
{
	return perfil.perfilValido();
}

bool PAGmodeloRevolucion::tiene(PAGvalores::PAGpartesRevolucion parte)
{
	switch (parte)
	{
	case PAGvalores::PAG_CUERPO:
		return vertices.size() > 0;
		break;
	case PAGvalores::PAG_TAPA_SUP:
		return hayTapaSuperior;
		break;
	case PAGvalores::PAG_TAPA_INF:
		return hayTapaInferior;
		break;
	default:
		break;
	}
}
