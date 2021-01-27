#include "PAGinstancia.h"

//Se asignan los valores por defecto a la matriz de modelado
PAGinstancia::PAGinstancia() :
	traslacion(0),
	rotacionX(0),
	rotacionY(0),
	rotacionZ(0),
	escalado(1)
{
}

void PAGinstancia::trasladar(glm::vec3 nuevaTraslacion)
{
	traslacion += nuevaTraslacion;
}

void PAGinstancia::escalar(glm::vec3 nuevoEscalado)
{
	if (nuevoEscalado.x != 0 && nuevoEscalado.y != 0 && nuevoEscalado.z != 0)
		escalado *= nuevoEscalado;
}

void PAGinstancia::rotarX(float grados)
{
	rotacionX += grados;
}

void PAGinstancia::rotarY(float grados)
{
	rotacionY += grados;

}

void PAGinstancia::rotarZ(float grados)
{
	rotacionZ += grados;
}

glm::mat4 PAGinstancia::matrizModelado(glm::vec3 centroModelo)
{
	glm::mat4 matrizTraslacion = glm::translate(traslacion);
	glm::vec3 centroTrasladado = glm::vec3(matrizTraslacion * glm::vec4(centroModelo, 0));
	glm::mat4 matrizRotacion = glm::translate(centroTrasladado) * glm::rotate(glm::radians(rotacionX), glm::vec3(1, 0, 0))
																* glm::rotate(glm::radians(rotacionY), glm::vec3(0, 1, 0))
																* glm::rotate(glm::radians(rotacionZ), glm::vec3(0, 0, 1)) * glm::translate(-centroTrasladado);
	glm::mat4 matrizEscalado = glm::translate(centroTrasladado) * glm::scale(escalado) * glm::translate(-centroTrasladado);
	return matrizTraslacion * matrizRotacion * matrizEscalado;
}
