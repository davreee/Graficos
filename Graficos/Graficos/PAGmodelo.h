#include <GL\glew.h>
#include <GL\GL.h>
#include "PAGvao.h"
#include "PAGmaterial.h"
#include "PAGinstancia.h"
#include "PAGtextura.h"
#include <stdexcept>
#include <vector>
#include "PAGnormalMap.h"
class PAGmodelo
{
private:
	GLenum modoVisualizacion;
	PAGvao* vao;
	PAGmaterial material;
	PAGtextura textura;
	PAGnormalMap normalMap;
	std::vector<PAGinstancia> instancias;
	glm::vec3 centroModelo;
	bool usaNormalMap;
public:
	enum tipoModelo {
		PAG_TRIANGULO, 
		PAG_CUADRADO, 
		PAG_TETRAEDRO,
		PAG_CUBO,
	};
	PAGmodelo(tipoModelo tipo,glm::vec3 colorAmbiente,glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho,
		std::string nombreNormalMap, float altoMap, float anchoMap);
	PAGmodelo(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normales, std::vector<glm::vec2>& coordenadasTextura, std::vector<GLuint> indices, glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho);
	~PAGmodelo();
	void pintate();
	void setmodoVisualizacion(GLenum modoVisualizacion);
	GLenum getmodoVisualizacion();
	glm::vec3 getColorAmbiente();
	glm::vec3 getColorDifuso();
	glm::vec3 getColorEspecular();
	GLfloat getShininess();
	bool getUsaNormalMap();
	void addInstancia();
	void trasladarInstancia(int numInstancia, glm::vec3 traslacion);
	void escalarInstancia(int numInstancia, glm::vec3 escalado);
	void rotarInstanciaX(int numInstancia, float grados);
	void rotarInstanciaY(int numInstancia, float grados);
	void rotarInstanciaZ(int numInstancia, float grados);
	std::vector<glm::mat4>* obtenerInstancias();
};

