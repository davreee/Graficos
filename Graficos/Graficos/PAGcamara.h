#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GL\glew.h>
#include <GL\GL.h>
#include <glm.hpp>
#include <ext.hpp>
#include <gtx/transform.hpp>

class PAGcamara
{
private:
	glm::vec3 posicion;
	glm::vec3 lookAt;
	GLfloat fovY;
	GLint ancho;
	GLint alto;
	GLfloat zNear;
	GLfloat zFar;
	GLfloat calcularFovY(GLfloat fovX);
	GLfloat calcularRadianes(GLfloat sexagesimales);
	GLfloat getAspecto();
	glm::vec3 vectorUp(glm::vec3 v);
public:
	PAGcamara();
	void setPosicion(glm::vec3 nuevaPos);
	void setPosicion(GLfloat x, GLfloat y, GLfloat z);
	void setLookAt(glm::vec3 nuevoLa);
	void setLookAt(GLfloat x, GLfloat y, GLfloat z);
	void setUp(GLfloat x, GLfloat y, GLfloat z);
	void setFovXrad(GLfloat radianes);
	void setFovXsex(GLfloat sexagesimales);
	void setFovYrad(GLfloat radianes);
	void setFovYsex(GLfloat sexagesimales);
	void setAncho(GLint ancho);
	void setAlto(GLint alto);
	void setZNear(GLfloat valor);
	void setZFar(GLfloat valor);
	glm::mat4 mVision();
	glm::mat4 mProyeccion();
	glm::mat4 mPV();
	void pan(float factor);
	void tilt(float factor);
	void truckDolly(float factorX, float factorY);
	void boom(float factor);
	void orbit(float factorX, float factorY);
	void zoom(float factor);


};

