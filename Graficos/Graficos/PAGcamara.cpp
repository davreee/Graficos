#include "PAGcamara.h"
#include <cmath>
#include <iostream>

PAGcamara::PAGcamara() :
	posicion(0, 0, 0),
	lookAt(0, 0, 0),
	fovY(0),
	ancho(0),
	alto(0),
	zNear(0),
	zFar(0)

{
}

void PAGcamara::setPosicion(glm::vec3 nuevaPos)
{
	posicion = nuevaPos;
}

void PAGcamara::setPosicion(GLfloat x, GLfloat y, GLfloat z)
{
	posicion = glm::vec3(x, y, z);
}

void PAGcamara::setLookAt(glm::vec3 nuevoLa)
{
	lookAt = nuevoLa;
}

void PAGcamara::setLookAt(GLfloat x, GLfloat y, GLfloat z)
{
	lookAt = glm::vec3(x, y, z);
}


void PAGcamara::setFovXrad(GLfloat radianes)
{
	fovY = calcularFovY(radianes);
}

void PAGcamara::setFovXsex(GLfloat sexagesimales)
{
	setFovXrad(calcularRadianes(sexagesimales));
}

void PAGcamara::setFovYrad(GLfloat radianes)
{
	fovY = radianes;
}

void PAGcamara::setFovYsex(GLfloat sexagesimales)
{
	fovY = calcularRadianes(sexagesimales);
}

void PAGcamara::setAncho(GLint ancho)
{
	this->ancho = ancho;
}

void PAGcamara::setAlto(GLint alto)
{
	this->alto = alto;
}

void PAGcamara::setZNear(GLfloat valor)
{
	zNear = valor;
}

void PAGcamara::setZFar(GLfloat valor)
{
	zFar = valor;
}

glm::mat4 PAGcamara::mVision()
{
	glm::vec3 n = posicion - lookAt;
	n = glm::normalize(n);
	return glm::lookAt(posicion, lookAt, vectorUp(n));
}

glm::mat4 PAGcamara::mProyeccion()
{
	return glm::perspective(fovY, getAspecto(), zNear, zFar);
}

glm::mat4 PAGcamara::mPV()
{
	return mProyeccion() * mVision();
}

void PAGcamara::pan(float factor)
{
	float radianes = 0.10 * factor;
	glm::vec3 n = posicion - lookAt;
	n = glm::normalize(n);
	glm::vec3 u = glm::cross(vectorUp(n), n);
	glm::vec3 v = glm::cross(n, u);
	glm::mat4 mRotacion = glm::translate(posicion) * glm::rotate(radianes, v) * glm::translate(-posicion);;
	glm::vec4 p = mRotacion * glm::vec4(lookAt, 1);
	lookAt = glm::vec3(p.x, p.y, p.z);

}

void PAGcamara::tilt(float factor)
{
	float radianes = 0.10 * factor;
	glm::vec3 n = posicion - lookAt;
	n = glm::normalize(n);
	glm::vec3 u = glm::cross(vectorUp(n), n);
	glm::vec3 v = glm::cross(n, u);
	glm::mat4 mRotacion = glm::translate(posicion) * glm::rotate(radianes, u) * glm::translate(-posicion);;
	glm::vec4 p = mRotacion * glm::vec4(lookAt, 1);
	lookAt = glm::vec3(p.x, p.y, p.z);
}

void PAGcamara::truckDolly(float factorX, float factorY)
{
	glm::mat4 mTransform = glm::translate(glm::vec3(factorX, 0, factorY));
	glm::vec4 nuevoLA = mTransform * glm::vec4(lookAt, 1);
	glm::vec4 nuevaP = mTransform * glm::vec4(posicion, 1);
	lookAt = glm::vec3(nuevoLA.x, nuevoLA.y, nuevoLA.z);
	posicion = glm::vec3(nuevaP.x, nuevaP.y, nuevaP.z);
}

void PAGcamara::boom(float factor)
{
	glm::mat4 mTransform = glm::translate(glm::vec3(0, factor, 0));
	glm::vec4 nuevoLA = mTransform * glm::vec4(lookAt, 1);
	glm::vec4 nuevaP = mTransform * glm::vec4(posicion, 1);
	lookAt = glm::vec3(nuevoLA.x, nuevoLA.y, nuevoLA.z);
	posicion = glm::vec3(nuevaP.x, nuevaP.y, nuevaP.z);
}

void PAGcamara::orbit(float factorX, float factorY)
{
	glm::vec3 n = posicion - lookAt;
	n = glm::normalize(n);
	glm::vec3 u = glm::cross(vectorUp(n), n);
	glm::vec3 v = glm::cross(n, u);
	glm::mat4 mRotacion = glm::translate(lookAt) * glm::rotate(glm::radians(factorX), v) * glm::rotate(glm::radians(factorY), u) * glm::translate(-lookAt);;
	glm::vec4 p = mRotacion * glm::vec4(posicion, 1);
	posicion = glm::vec3(p.x, p.y, p.z);
}

void PAGcamara::zoom(float factor)
{
	if (glm::degrees(fovY) > 35.0f && glm::degrees(fovY) < 90.0)
		fovY += glm::radians(factor);
	if (glm::degrees(fovY) <= 35.0f)
		fovY = glm::radians(35.0f);
	if (glm::degrees(fovY) >= 90.0f)
		fovY = glm::radians(90.0f);

}

GLfloat PAGcamara::calcularFovY(GLfloat fovX)
{
	return 2 * (atan((tan((fovX / 2)) / getAspecto())));
}

GLfloat PAGcamara::calcularRadianes(GLfloat sexagesimales)
{
	double pi = 3.1415926535897;
	return ((2 * pi) * sexagesimales) / 360;
}

GLfloat PAGcamara::getAspecto()
{
	return (GLfloat)(ancho / alto);
}

glm::vec3 PAGcamara::vectorUp(glm::vec3 v)
{

	if (glm::all(glm::epsilonEqual(v, glm::vec3(0, 1, 0), (float).15))) {
		return glm::vec3(0, 0, 1);
	}
	if (glm::all(glm::epsilonEqual(v, glm::vec3(0, -1, 0), (float).15))) {
		return glm::vec3(0, 0, -1);
	}

	return glm::vec3(0, 1, 0);

}
