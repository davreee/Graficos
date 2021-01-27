#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GL\glew.h>
#include <GL\GL.h>
#include <glm.hpp>
#include <ext.hpp>
#include <gtx/transform.hpp>
class PAGinstancia
{
private:
	glm::vec3 traslacion;
	float rotacionX;
	float rotacionY;
	float rotacionZ;
	glm::vec3 escalado;
public:
	PAGinstancia();
	void trasladar(glm::vec3 nuevaTraslacion);
	void escalar(glm::vec3 nuevoEscalado);
	void rotarX(float grados);
	void rotarY(float grados);
	void rotarZ(float grados);
	glm::mat4 matrizModelado(glm::vec3 centroModelo);
};

