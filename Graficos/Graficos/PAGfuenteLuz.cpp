#include "PAGfuenteLuz.h"

PAGfuenteLuz::PAGfuenteLuz(glm::vec3 iAmbiente):
	tipoLuz(PAGvalores::PAGTipoLuz::PAG_AMBIENTE),
	intensidadAmbiente(iAmbiente)
{
}

PAGfuenteLuz::PAGfuenteLuz(PAGvalores::PAGTipoLuz tipo, glm::vec3 posDir, glm::vec3 iDifusa, glm::vec3 iEspecular):
	tipoLuz(tipo)
{
	if (tipoLuz == PAGvalores::PAGTipoLuz::PAG_PUNTUAL) {
		posicion = posDir;
	}
	if (tipoLuz == PAGvalores::PAGTipoLuz::PAG_DIRECCIONAL) {
		direccion = posDir;
	}
	intensidadDifusa = iDifusa;
	intensidadEspecular = iEspecular;
}

PAGfuenteLuz::PAGfuenteLuz(glm::vec3 pos, glm::vec3 dir, glm::vec3 iDifusa, glm::vec3 iEspecular, GLfloat anguloApertura) :
	tipoLuz(PAGvalores::PAGTipoLuz::PAG_SPOT),
	posicion(pos),
	direccion(dir),
	intensidadDifusa(iDifusa),
	intensidadEspecular(iEspecular),
	apertura(anguloApertura)
{
}

glm::vec3 PAGfuenteLuz::getIntensidadAmbiente()
{
	return intensidadAmbiente;
}

glm::vec3 PAGfuenteLuz::getIntensidadDifusa()
{
	return intensidadDifusa;
}

glm::vec3 PAGfuenteLuz::getIntensidadEspecular()
{
	return intensidadEspecular;
}

glm::vec3 PAGfuenteLuz::getPosicion()
{
	return posicion;
}

glm::vec3 PAGfuenteLuz::getDireccion()
{
	return direccion;
}

GLfloat PAGfuenteLuz::getApertura()
{
	return apertura;
}
