#include "PAGrenderer.h"
#include <stdlib.h>
#include <math.h>
#include <stdexcept>
#include <glm.hpp>
#include <iostream>


PAGrenderer* PAGrenderer::instancia = nullptr;

PAGrenderer::PAGrenderer() :
	colorComponenteR(0.3),
	colorComponenteG(0.6),
	colorComponenteB(0.9),
	colorComponenteA(1.0),
	luzAmbiente(nullptr),
	luzPuntual(nullptr),
	luzPuntualActiva(false),
	luzSpot(nullptr),
	luzSpotActiva(false),
	modelos(),
	modelosRevolucion(),
	camara(nullptr),
	pointSize(5),
	animacionActiva(false)
{

	modelos.push_back(new PAGmodelo(PAGmodelo::PAG_CUADRADO, glm::vec3(1, 0.5, 0.31), glm::vec3(.5, .5, .31), glm::vec3(.0, .0, 0.0), GLfloat(60), "mesa.png", 512, 512, "mesaNormalMap.png", 512, 512));
	std::vector<glm::vec2> puntos;

	puntos.push_back(glm::vec2(0, 0));
	puntos.push_back(glm::vec2(1, 0));
	puntos.push_back(glm::vec2(1, 2));
	puntos.push_back(glm::vec2(0.85, 2.25));
	puntos.push_back(glm::vec2(0, 2.25));

	PAGmodeloRevolucion* lataRevolucion = new PAGmodeloRevolucion(puntos, 0, 40, 0);
	lataRevolucion->trasladar(glm::vec3(3, -1, -3));
	if (lataRevolucion->esValido()) {
		modelosRevolucion.push_back(lataRevolucion);
	}
	puntos.clear();
	puntos.push_back(glm::vec2(0, 0.125));
	puntos.push_back(glm::vec2(0.125, 0));
	puntos.push_back(glm::vec2(2, 0.125));
	puntos.push_back(glm::vec2(1, 1));
	puntos.push_back(glm::vec2(2, 2));
	puntos.push_back(glm::vec2(0.225, 1.975));
	puntos.push_back(glm::vec2(0, 2));
	PAGmodeloRevolucion* modeloRevolucion = new PAGmodeloRevolucion(puntos, 1, 40, 1);
	modeloRevolucion->trasladar(glm::vec3(3, -1, 0));
	if (modeloRevolucion->esValido()) {
		modelosRevolucion.push_back(modeloRevolucion);
	}

}

PAGrenderer::~PAGrenderer() {
	if (shaderLuzAmbiente != nullptr)
		delete shaderLuzAmbiente;
	if (shaderLuzPuntualBump != nullptr)
		delete shaderLuzPuntualBump;
	if (shaderLuzSpotBump != nullptr)
		delete shaderLuzSpotBump;
	if (camara != nullptr)
		delete camara;
	for (PAGmodelo* modelo : modelos) {
		delete modelo;
	}
	for(PAGmodeloRevolucion* modeloR: modelosRevolucion) {
		delete modeloR;
	}
}

void PAGrenderer::rellenarFondo()
{
	glClearColor(colorComponenteR, colorComponenteG, colorComponenteB, colorComponenteA);
}

void PAGrenderer::addModelo(PAGmodelo::tipoModelo tipo, glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho, std::string nombreNormalMap, float altoMap, float anchoMap)
{
	modelos.push_back(new PAGmodelo(tipo, colorAmbiente, colorDifuso, colorEspecular, brillo, nombreTextura, alto, ancho, nombreNormalMap, altoMap, anchoMap));
}

void PAGrenderer::addModelo(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normales, std::vector<glm::vec2>& coordenadasTextura, std::vector<GLuint> indices, glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho)
{
	modelos.push_back(new PAGmodelo(vertices, normales, coordenadasTextura, indices, colorAmbiente, colorDifuso, colorEspecular, brillo, nombreTextura, alto, ancho));
}

void PAGrenderer::addInstancia(int idModelo)
{
	if (idModelo < 0 || idModelo > modelos.size())
		throw std::out_of_range("PAGrenderer::trasladarInstancia: no existe un modelo con dicho id");

	modelos.at(idModelo)->addInstancia();
}

void PAGrenderer::trasladarInstancia(int idModelo, int numInstancia, glm::vec3 traslacion)
{
	if (idModelo < 0 || idModelo > modelos.size())
		throw std::out_of_range("PAGrenderer::trasladarInstancia: no existe un modelo con dicho id");

	try {
		modelos.at(idModelo)->trasladarInstancia(numInstancia, traslacion);
	}
	catch (std::out_of_range e) {
		throw std::out_of_range(e);
	}
}

void PAGrenderer::escalarInstancia(int idModelo, int numInstancia, glm::vec3 escalado)
{
	if (idModelo < 0 || idModelo > modelos.size())
		throw std::out_of_range("PAGrenderer::escalarInstancia: no existe un modelo con dicho id");
	try {
		modelos.at(idModelo)->escalarInstancia(numInstancia, escalado);
	}
	catch (std::out_of_range e) {
		throw std::out_of_range(e);
	}
}

void PAGrenderer::rotarInstanciaX(int idModelo, int numInstancia, float grados)
{
	if (idModelo < 0 || idModelo > modelos.size())
		throw std::out_of_range("PAGrenderer::rotarInstanciaX: no existe un modelo con dicho id");
	try {

		modelos.at(idModelo)->rotarInstanciaX(numInstancia, grados);
	}
	catch (std::out_of_range e) {
		throw std::out_of_range(e);
	}
}

void PAGrenderer::rotarInstanciaY(int idModelo, int numInstancia, float grados)
{
	if (idModelo < 0 || idModelo > modelos.size())
		throw std::out_of_range("PAGrenderer::rotarInstanciaY: no existe un modelo con dicho id");
	try {

		modelos.at(idModelo)->rotarInstanciaY(numInstancia, grados);
	}
	catch (std::out_of_range e) {
		throw std::out_of_range(e);
	}


}

void PAGrenderer::rotarInstanciaZ(int idModelo, int numInstancia, float grados)
{
	if (idModelo < 0 || idModelo > modelos.size())
		throw std::out_of_range("PAGrenderer::rotarInstanciaZ: no existe un modelo con dicho id");
	try {

		modelos.at(idModelo)->rotarInstanciaZ(numInstancia, grados);
	}
	catch (std::out_of_range e) {
		throw std::out_of_range(e);
	}
}

void PAGrenderer::addLuzAmbiente(glm::vec3 intensidadAmbiente)
{
	if (luzAmbiente != nullptr) {
		delete luzAmbiente;
		luzAmbiente = nullptr;
	}
	luzAmbiente = new PAGfuenteLuz(intensidadAmbiente);
}

void PAGrenderer::addLuzPuntual(glm::vec3 intensidadDifusa, glm::vec3 intensidadEspecular, glm::vec3 posicion)
{
	if (luzPuntual != nullptr) {
		delete luzPuntual;
		luzPuntual = nullptr;
	}
	luzPuntual = new PAGfuenteLuz(PAGvalores::PAGTipoLuz::PAG_PUNTUAL, posicion, intensidadDifusa, intensidadEspecular);
	luzPuntualActiva = true;
}

void PAGrenderer::addLuzSpot(glm::vec3 intensidadDifusa, glm::vec3 intensidadEspecular, glm::vec3 posicion, glm::vec3 direccion, GLfloat apertura)
{
	if (luzSpot != nullptr) {
		delete luzSpot;
		luzSpot = nullptr;
	}
	luzSpot = new PAGfuenteLuz(posicion, direccion, intensidadDifusa, intensidadEspecular, apertura);
	luzSpotActiva = true;
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
	if (camara == nullptr) {
		camara = new PAGcamara();
	}
	camara->setAncho(ancho);
	camara->setAlto(alto);
}

void PAGrenderer::cambioColorFondo(int modo)
{
	if (modo == 0) {
		//Baja la ruedecilla
		colorComponenteR -= cambioColorAleatorio();
		colorComponenteG -= cambioColorAleatorio();
		colorComponenteB -= cambioColorAleatorio();
	}
	else
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
	glDepthFunc(GL_LEQUAL);
}

void PAGrenderer::addColorBorrado(GLclampf incremento) {

	//A�adimos el incremento a cada componente
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

	//A�adimos el incremento correspondiente a cada componente
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

void PAGrenderer::borraBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PAGrenderer::refrescaVentana()
{
	borraBuffers();
	//Como sabemos hay que activar el shader program cada vez que se va a dibujar la escena
	glm::mat4 mPV = camara->mPV();
	glm::mat4 mV = camara->mVision();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < modelos.size(); i++) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::vector <glm::mat4>* instanciasObjeto = modelos.at(i)->obtenerInstancias();
		shaderLuzAmbiente->activar();
		try {
			shaderLuzAmbiente->setUniform("mPV", mPV);
			shaderLuzAmbiente->setUniform("pointSize", pointSize);
			shaderLuzAmbiente->setUniform("Ia", luzAmbiente->getIntensidadAmbiente());
			shaderLuzAmbiente->setUniform("TexSamplerColor", 0);
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
		for (int j = 0; j < instanciasObjeto->size(); j++) {
			try {
				shaderLuzAmbiente->setUniform("mM", instanciasObjeto->at(j));
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
			modelos.at(i)->pintate();
		}

		if (luzPuntualActiva) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			if (modelos.at(i)->getUsaNormalMap()) {
				shaderLuzPuntualBump->activar();
				glm::vec4 posicionLuzVision = mV * glm::vec4(luzPuntual->getPosicion(), 1);
				try {
					shaderLuzPuntualBump->setUniform("pointSize", pointSize);
					shaderLuzPuntualBump->setUniform("mPV", mPV);
					shaderLuzPuntualBump->setUniform("mView", mV);
					shaderLuzPuntualBump->setUniform("Id", luzPuntual->getIntensidadDifusa());
					shaderLuzPuntualBump->setUniform("Ks", modelos.at(i)->getColorEspecular());
					shaderLuzPuntualBump->setUniform("Is", luzPuntual->getIntensidadEspecular());
					shaderLuzPuntualBump->setUniform("shininess", modelos.at(i)->getShininess());
					shaderLuzPuntualBump->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
					shaderLuzPuntualBump->setUniform("TexSamplerColor", 0);
					shaderLuzPuntualBump->setUniform("TexSamplerBump", 1);
				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
				for (int j = 0; j < instanciasObjeto->size(); j++) {
					try {
						shaderLuzPuntualBump->setUniform("mModel", instanciasObjeto->at(j));
					}
					catch (std::exception e) {
						std::cout << e.what() << std::endl;
					}

					//Pintamos el modelo
					modelos.at(i)->pintate();
				}
			}
			else {
				shaderLuzPuntual->activar();
				glm::vec4 posicionLuzVision = mV * glm::vec4(luzPuntual->getPosicion(), 1);
				try {
					shaderLuzPuntual->setUniform("pointSize", pointSize);
					shaderLuzPuntual->setUniform("mPV", mPV);
					shaderLuzPuntual->setUniform("mView", mV);
					shaderLuzPuntual->setUniform("Id", luzPuntual->getIntensidadDifusa());
					shaderLuzPuntual->setUniform("Ks", modelos.at(i)->getColorEspecular());
					shaderLuzPuntual->setUniform("Is", luzPuntual->getIntensidadEspecular());
					shaderLuzPuntual->setUniform("shininess", modelos.at(i)->getShininess());
					shaderLuzPuntual->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
					shaderLuzPuntual->setUniform("TexSamplerColor", 0);
				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
				for (int j = 0; j < instanciasObjeto->size(); j++) {
					try {
						shaderLuzPuntual->setUniform("mModel", instanciasObjeto->at(j));
					}
					catch (std::exception e) {
						std::cout << e.what() << std::endl;
					}

					//Pintamos el modelo
					modelos.at(i)->pintate();
				}
			}
		}

		if (luzSpotActiva) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			if (modelos.at(i)->getUsaNormalMap()) {
				shaderLuzSpotBump->activar();
				//Asignamos los uniforms	
				glm::vec4 direccionVision = mV * glm::vec4(luzSpot->getDireccion(), 1);
				glm::vec4 posicionLuzVision = mV * glm::vec4(luzSpot->getPosicion(), 1);
				try {
					shaderLuzSpotBump->setUniform("mPV", mPV);
					shaderLuzSpotBump->setUniform("pointSize", pointSize);
					shaderLuzSpotBump->setUniform("mView", mV);
					shaderLuzSpotBump->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
					shaderLuzSpotBump->setUniform("lightDirection", glm::vec3(direccionVision.x, direccionVision.y, direccionVision.z));
					shaderLuzSpotBump->setUniform("Ks", modelos.at(i)->getColorEspecular());
					shaderLuzSpotBump->setUniform("Id", luzSpot->getIntensidadDifusa());
					shaderLuzSpotBump->setUniform("Is", luzSpot->getIntensidadEspecular());
					shaderLuzSpotBump->setUniform("shininess", modelos.at(i)->getShininess());
					shaderLuzSpotBump->setUniform("spotAngle", luzSpot->getApertura());
					shaderLuzSpotBump->setUniform("TexSamplerColor", 0);
					shaderLuzSpotBump->setUniform("TexSamplerBump", 1);

				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
				for (int j = 0; j < instanciasObjeto->size(); j++) {
					try {
						shaderLuzSpotBump->setUniform("mModel", instanciasObjeto->at(j));
					}
					catch (std::exception e) {
						std::cout << e.what() << std::endl;
					}
					modelos.at(i)->pintate();
				}
			}
			else {
				shaderLuzSpot->activar();
				//Asignamos los uniforms	
				glm::vec4 direccionVision = mV * glm::vec4(luzSpot->getDireccion(), 1);
				glm::vec4 posicionLuzVision = mV * glm::vec4(luzSpot->getPosicion(), 1);
				try {
					shaderLuzSpot->setUniform("mPV", mPV);
					shaderLuzSpot->setUniform("pointSize", pointSize);
					shaderLuzSpot->setUniform("mView", mV);
					shaderLuzSpot->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
					shaderLuzSpot->setUniform("lightDirection", glm::vec3(direccionVision.x, direccionVision.y, direccionVision.z));
					shaderLuzSpot->setUniform("Ks", modelos.at(i)->getColorEspecular());
					shaderLuzSpot->setUniform("Id", luzSpot->getIntensidadDifusa());
					shaderLuzSpot->setUniform("Is", luzSpot->getIntensidadEspecular());
					shaderLuzSpot->setUniform("shininess", modelos.at(i)->getShininess());
					shaderLuzSpot->setUniform("spotAngle", luzSpot->getApertura());
					shaderLuzSpot->setUniform("TexSamplerColor", 0);

				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
				for (int j = 0; j < instanciasObjeto->size(); j++) {
					try {
						shaderLuzSpot->setUniform("mModel", instanciasObjeto->at(j));
					}
					catch (std::exception e) {
						std::cout << e.what() << std::endl;
					}
					modelos.at(i)->pintate();
				}
			}
		}
	}

	for (int i = 0; i < modelosRevolucion.size(); i++)
	{

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		shaderLuzAmbiente->activar();

		try {
			shaderLuzAmbiente->setUniform("mPV", mPV);
			shaderLuzAmbiente->setUniform("pointSize", pointSize);
			shaderLuzAmbiente->setUniform("Ia", luzAmbiente->getIntensidadAmbiente());
			shaderLuzAmbiente->setUniform("TexSamplerColor", 0);
			shaderLuzAmbiente->setUniform("mM", modelosRevolucion.at(i)->obtenerInstancia());
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
		modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_CUERPO);

		if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP) || modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF)) {
			shaderLuzAmbienteNoText->activar();
			//Asignamos los uniforms
			try {
				shaderLuzAmbienteNoText->setUniform("mPV", mPV);
				shaderLuzAmbienteNoText->setUniform("pointSize", pointSize);
				shaderLuzAmbienteNoText->setUniform("Ka", glm::vec3(0.3, 0.3, 0.3));
				shaderLuzAmbienteNoText->setUniform("Ia", luzAmbiente->getIntensidadAmbiente());
				shaderLuzAmbiente->setUniform("mM", modelosRevolucion.at(i)->obtenerInstancia());
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
			if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP)) modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP);
			if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF)) modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF);
		}

		if (luzPuntualActiva) {

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			shaderLuzPuntual->activar();
			glm::vec4 posicionLuzVision = mV * glm::vec4(luzPuntual->getPosicion(), 1);
			try {
				shaderLuzPuntual->setUniform("pointSize", pointSize);
				shaderLuzPuntual->setUniform("mPV", mPV);
				shaderLuzPuntual->setUniform("mView", mV);
				shaderLuzPuntual->setUniform("Id", luzPuntual->getIntensidadDifusa());
				shaderLuzPuntual->setUniform("Ks", glm::vec3(1.0, 1.0, 1.0));
				shaderLuzPuntual->setUniform("Is", luzPuntual->getIntensidadEspecular());
				shaderLuzPuntual->setUniform("shininess", 250);
				shaderLuzPuntual->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
				shaderLuzPuntual->setUniform("TexSamplerColor", 0);
				shaderLuzPuntual->setUniform("mModel", modelosRevolucion.at(i)->obtenerInstancia());

			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
			modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_CUERPO);


			if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP) || modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF)) {
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				shaderLuzPuntualNoText->activar();

				//Asignamos los uniforms
				try {
					glm::vec4 posicionLuzVision = mV * glm::vec4(luzPuntual->getPosicion(), 1);
					shaderLuzPuntualNoText->setUniform("mPV", mPV);
					shaderLuzPuntualNoText->setUniform("pointSize", pointSize);
					//LuzPuntual
					shaderLuzPuntualNoText->setUniform("mView", mV);
					shaderLuzPuntualNoText->setUniform("mModel", modelosRevolucion.at(i)->obtenerInstancia());
					shaderLuzPuntualNoText->setUniform("Kd", glm::vec3(0.6, 0.6, 0.6));
					shaderLuzPuntualNoText->setUniform("Ks", glm::vec3(1.0, 1.0, 1.0));
					shaderLuzPuntualNoText->setUniform("Id", luzPuntual->getIntensidadDifusa());
					shaderLuzPuntualNoText->setUniform("Is", luzPuntual->getIntensidadEspecular());
					shaderLuzPuntualNoText->setUniform("shininess", 250);
					shaderLuzPuntualNoText->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));

				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
				if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP)) modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP);
				if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF)) modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF);
			}
		}

		if (luzSpotActiva) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			shaderLuzSpot->activar();
			//Asignamos los uniforms	
			glm::vec4 direccionVision = mV * glm::vec4(luzSpot->getDireccion(), 1);
			glm::vec4 posicionLuzVision = mV * glm::vec4(luzSpot->getPosicion(), 1);
			try {
				shaderLuzSpot->setUniform("mPV", mPV);
				shaderLuzSpot->setUniform("pointSize", pointSize);
				shaderLuzSpot->setUniform("mView", mV);
				shaderLuzSpot->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
				shaderLuzSpot->setUniform("lightDirection", glm::vec3(direccionVision.x, direccionVision.y, direccionVision.z));
				shaderLuzSpot->setUniform("Ks", glm::vec3(1.0, 1.0, 1.0));
				shaderLuzSpot->setUniform("Id", luzSpot->getIntensidadDifusa());
				shaderLuzSpot->setUniform("Is", luzSpot->getIntensidadEspecular());
				shaderLuzSpot->setUniform("shininess", 250);
				shaderLuzSpot->setUniform("spotAngle", luzSpot->getApertura());
				shaderLuzSpot->setUniform("TexSamplerColor", 0);
				shaderLuzSpot->setUniform("mModel", modelosRevolucion.at(i)->obtenerInstancia());
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}

			modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_CUERPO);

			if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP) || modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF)) {
				shaderLuzSpotNoText->activar();
				//Asignamos los uniforms	
				try {
					shaderLuzSpotNoText->setUniform("mPV", mPV);
					shaderLuzSpotNoText->setUniform("pointSize", pointSize);
					shaderLuzSpotNoText->setUniform("mView", mV);
					shaderLuzSpotNoText->setUniform("lightPosition", glm::vec3(posicionLuzVision.x, posicionLuzVision.y, posicionLuzVision.z));
					shaderLuzSpotNoText->setUniform("lightDirection", glm::vec3(direccionVision.x, direccionVision.y, direccionVision.z));
					shaderLuzSpotNoText->setUniform("Ks", glm::vec3(1.0, 1.0, 1.0));
					shaderLuzSpotNoText->setUniform("Id", luzSpot->getIntensidadDifusa());
					shaderLuzSpotNoText->setUniform("Is", luzSpot->getIntensidadEspecular());
					shaderLuzSpotNoText->setUniform("shininess", 250);
					shaderLuzSpotNoText->setUniform("spotAngle", luzSpot->getApertura());
					shaderLuzSpotNoText->setUniform("mModel", modelosRevolucion.at(i)->obtenerInstancia());
				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
				if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP)) modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_TAPA_SUP);
				if (modelosRevolucion.at(i)->tiene(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF)) modelosRevolucion.at(i)->pintar(PAGvalores::PAGpartesRevolucion::PAG_TAPA_INF);
			}

		}
	}
}

float PAGrenderer::cambioColorAleatorio() {
	return  ((rand() % 5) + 1) * 0.01;
}

void PAGrenderer::vistaPlanta()
{
	camara->setPosicion(0, 8, 0);
	camara->setLookAt(0, 0, 0);
	camara->setFovXsex(60);
	camara->setZFar(35);
	camara->setZNear(2);
}

void PAGrenderer::vistaAlzado()
{
	camara->setPosicion(0, 1, 10);
	camara->setLookAt(0, 1, 0);
	camara->setFovXsex(60);
	camara->setZFar(35);
	camara->setZNear(2);
}

void PAGrenderer::vistaPerfil()
{
	camara->setPosicion(8, 1, 0);
	camara->setLookAt(0, 1, 0);
	camara->setFovXsex(60);
	camara->setZFar(35);
	camara->setZNear(2);
}

void PAGrenderer::vistaDiagonal()
{
	camara->setPosicion(5, 5, 5);
	camara->setLookAt(0, 0, 0);
	camara->setFovXsex(60);
	camara->setZFar(35);
	camara->setZNear(2);
}

void PAGrenderer::activarSizePoint()
{
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void PAGrenderer::activarBlending()
{
	glEnable(GL_BLEND);
}

void PAGrenderer::activarLuzPuntual()
{
	luzPuntualActiva = !luzPuntualActiva;
}

void PAGrenderer::activarLuzSpot()
{
	luzSpotActiva = !luzSpotActiva;
}

void PAGrenderer::activarAnimacion()
{
	animacionActiva = !animacionActiva;
}

void PAGrenderer::activarSaltoPrimitiva()
{
	glPrimitiveRestartIndex(0xFFFF);
	glEnable(GL_PRIMITIVE_RESTART);
}

void PAGrenderer::moverCamara(PAGvalores::PAGtipoMovimiento modoMovimiento, double factorX, double factorY)
{
	switch (modoMovimiento)
	{
	case PAGvalores::PAGtipoMovimiento::PAG_PAN:
		camara->pan(factorX);
		break;
	case PAGvalores::PAGtipoMovimiento::PAG_TILT:
		camara->tilt(factorY);
		break;
	case PAGvalores::PAGtipoMovimiento::PAG_TRUCK:
		camara->truckDolly(factorX, factorY);
	case PAGvalores::PAGtipoMovimiento::PAG_BOOM:
		camara->boom(factorY);
		break;
	case PAGvalores::PAGtipoMovimiento::PAG_ORBIT:
		camara->orbit(factorX, factorY);
		break;
	case PAGvalores::PAGtipoMovimiento::PAG_ZOOM:
		camara->zoom(factorX);
		break;
	default:
		break;
	}
}

void PAGrenderer::crearShaders()
{
	shaderLuzAmbiente = new PAGshaderProgram();
	try
	{
		shaderLuzAmbiente->creaShaderProgram("luzAmbiente");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzAmbiente->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

	shaderLuzAmbienteNoText = new PAGshaderProgram();

	try
	{
		shaderLuzAmbienteNoText->creaShaderProgram("luzAmbienteNoText");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzAmbienteNoText->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

	//Creamos el shader
	shaderLuzPuntualBump = new PAGshaderProgram();
	try
	{
		shaderLuzPuntualBump->creaShaderProgram("luzPuntualBump");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzPuntualBump->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

	shaderLuzSpotBump = new PAGshaderProgram();
	try
	{
		shaderLuzSpotBump->creaShaderProgram("luzSpotBump");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzSpotBump->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

	shaderLuzPuntual = new PAGshaderProgram();
	try
	{
		shaderLuzPuntual->creaShaderProgram("luzPuntual");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzPuntual->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

	shaderLuzPuntualNoText = new PAGshaderProgram();
	try
	{
		shaderLuzPuntualNoText->creaShaderProgram("luzPuntualNoText");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzPuntualNoText->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}



	shaderLuzSpot = new PAGshaderProgram();
	try
	{
		shaderLuzSpot->creaShaderProgram("luzSpot");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzSpot->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

	shaderLuzSpotNoText = new PAGshaderProgram();
	try
	{
		shaderLuzSpotNoText->creaShaderProgram("luzSpotNoText");

	}
	catch (std::runtime_error e) {
		std::string excepcion = e.what();
		excepcion += "\n" + shaderLuzSpotNoText->getMensajeGLSL();
		throw std::runtime_error(excepcion);
	}
	catch (std::invalid_argument e) {
		throw e;
	}

}

PAGrenderer* PAGrenderer::getInstancia() {
	if (!instancia) {
		instancia = new PAGrenderer();
	}

	return instancia;
}