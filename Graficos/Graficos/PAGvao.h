#include <GL\glew.h>
#include <GL\GL.h>
#include <glm.hpp>
#include <vector>
#pragma once
class PAGvao
{
private:
	GLuint identificador;
	GLuint vboVertices;
	GLuint vboNormales;
	GLuint vboTextCoor;
	GLuint vboTangentes;
	GLuint iboAlambre;
	GLuint iboPuntos;
	GLuint iboSolido;
	GLuint iboMalla;
	GLuint iboAbanico;
	bool listo;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normales;
	std::vector<glm::vec2> textCoor;
	std::vector<glm::vec3> tangentes;
	std::vector<GLuint> indicesAlambre;
	std::vector<GLuint> indicesPuntos;
	std::vector<GLuint> indicesSolido;
	std::vector<GLuint> indicesMalla;
	std::vector<GLuint> indicesAbanico;
public:
	PAGvao();
	~PAGvao();
	void addVertice(glm::vec3 vertice);
	void addNormal(glm::vec3 normal);
	void addTextCoor(glm::vec2 coordenada);
	void addIndice(GLenum modoDibujo, GLuint valor);
	void addTangente(glm::vec3 tangente);
	void generaArray();
	void activaArray(GLenum modoDibujo);
	void pintaArray(GLenum modoDibujo);
	bool listoParaDibujar();


};

