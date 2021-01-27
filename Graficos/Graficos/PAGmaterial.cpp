#include "PAGmaterial.h"



PAGmaterial::PAGmaterial(glm::vec3 cAmbiente, glm::vec3 cDifuso, glm::vec3 cEspecular, GLfloat brillo):
	colorAmbiente(cAmbiente),
	colorDifuso(cDifuso),
	colorEspecular(cEspecular),
	shininess(brillo)
{
}

glm::vec3 PAGmaterial::getColorAmbiente()
{
	return colorAmbiente;
}

glm::vec3 PAGmaterial::getColorDifuso()
{
	return colorDifuso;
}

glm::vec3 PAGmaterial::getColorEspecular()
{
	return colorEspecular;
}

GLfloat PAGmaterial::getShininess()
{
	return shininess;
}
