#define GLM_ENABLE_EXPERIMENTAL
#include <GL\glew.h>
#include <GL\GL.h>
#include <glm.hpp>
#include <ext.hpp>
#include <gtx/transform.hpp>
#include <string>
#include "PAGshaderProgram.h"
#include "PAGmodelo.h"
#include "PAGcamara.h"
#include "PAGvalores.h"
#include "PAGfuenteLuz.h"
#include "PAGtextura.h"
#include "PAGinstancia.h"
#include "PAGnormalMap.h"
#include "PAGmodeloRevolucion.h"
class PAGrenderer
{
private:
	static PAGrenderer* instancia;
	PAGrenderer();
	//Variables que almacenan el color de la escena
	float colorComponenteR;
	float colorComponenteG;
	float colorComponenteB;
	float colorComponenteA;
	//Función que genera el cambio que tendrá la componente aleatoriamente en el rango [0.01, 0.05]
	float cambioColorAleatorio();
	//Shaders de la luz
	PAGshaderProgram* shaderLuzAmbiente;
	PAGshaderProgram* shaderLuzAmbienteNoText;
	PAGshaderProgram* shaderLuzPuntualBump;
	PAGshaderProgram* shaderLuzSpotBump;
	PAGshaderProgram* shaderLuzPuntual;
	PAGshaderProgram* shaderLuzPuntualNoText;
	PAGshaderProgram* shaderLuzSpot;
	PAGshaderProgram* shaderLuzSpotNoText;
	//Modelos de la escena
	std::vector<PAGmodelo*> modelos;
	std::vector<PAGmodeloRevolucion*> modelosRevolucion;

	//Cámara de la escena
	PAGcamara* camara;
	//Tamaño de punto para la visualizción de dicho modo
	GLfloat pointSize;
	//Luces de la escena
	PAGfuenteLuz* luzAmbiente;
	PAGfuenteLuz* luzPuntual;
	PAGfuenteLuz* luzSpot;
	bool luzPuntualActiva;
	bool luzSpotActiva;
	bool animacionActiva;
public:
	static PAGrenderer* getInstancia();
	void rellenarFondo();
	void addModelo(PAGmodelo::tipoModelo tipo, glm::vec3 colorAmbiente,glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho,
		std::string nombreNormalMap, float altoMap, float anchoMap);
	void addModelo(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normales, std::vector<glm::vec2>& coordenadasTextura, std::vector<GLuint> indices, glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho);
	void addInstancia(int idModelo);
	void trasladarInstancia(int idModelo, int numInstancia, glm::vec3 traslacion);
	void escalarInstancia(int idModelo, int numInstancia, glm::vec3 escalado);
	void rotarInstanciaX(int idModelo, int numInstancia, float grados);
	void rotarInstanciaY(int idModelo, int numInstancia, float grados);
	void rotarInstanciaZ(int idModelo, int numInstancia, float grados);
	void addLuzAmbiente(glm::vec3 intensidadAmbiente);
	void addLuzPuntual(glm::vec3 intensidadDifusa, glm::vec3 intensidadEspecular, glm::vec3 posicion);
	void addLuzSpot(glm::vec3 intensidadDifusa, glm::vec3 intensidadEspecular, glm::vec3 posicion, glm::vec3 direccion, GLfloat apertura);
	void addColorBorrado(GLclampf incremento);
	void addColorBorrado(GLclampf incrementoR, GLclampf incrementoG, GLclampf incrementoB, GLclampf incrementoA);
	void borraBuffers();
	void refrescaVentana();
	void setColorBorrado(GLclampf incrementoR, GLclampf incrementoG, GLclampf incrementoB, GLclampf incrementoA);
	void setViewport(GLuint orX, GLuint orY, GLsizei ancho, GLsizei alto);
	void cambioColorFondo(int modo);
	void activarZBuffer();
	~PAGrenderer();
	void vistaPlanta();
	void vistaAlzado();
	void vistaPerfil();
	void vistaDiagonal();
	void activarSizePoint();
	void activarBlending();
	void activarLuzPuntual();
	void activarLuzSpot();
	void activarAnimacion();
	void activarSaltoPrimitiva();
	void moverCamara(PAGvalores::PAGtipoMovimiento modoMovimiento, double factorX, double factorY);
	void crearShaders();

};

