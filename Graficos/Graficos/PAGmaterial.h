#pragma once
#include <glm.hpp>
#include <GL\glew.h>
#include <gl\GL.h>
class PAGmaterial
{
private:
	glm::vec3 colorAmbiente;
	glm::vec3 colorDifuso;
	glm::vec3 colorEspecular;
	GLfloat shininess;
public:
	PAGmaterial(glm::vec3 cAmbiente, glm::vec3 cDifuso, glm::vec3 cEspecular, GLfloat brillo);
	glm::vec3 getColorAmbiente();
	glm::vec3 getColorDifuso();
	glm::vec3 getColorEspecular();
	GLfloat getShininess();
};

