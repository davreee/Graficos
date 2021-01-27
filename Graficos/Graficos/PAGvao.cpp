#include "PAGvao.h"

PAGvao::PAGvao() :identificador(0),
vboVertices(0),
vboNormales(0),
vboTextCoor(0),
vboTangentes(0),
iboAlambre(0),
iboPuntos(0),
iboSolido(0),
iboAbanico(0),
vertices(),
normales(),
textCoor(),
tangentes(),
indicesAlambre(),
indicesPuntos(),
indicesSolido(),
indicesMalla(),
indicesAbanico(),
listo(false)
{

}

PAGvao::~PAGvao()
{

}

void PAGvao::addVertice(glm::vec3 vertice)
{
	vertices.push_back(vertice);
}

void PAGvao::addNormal(glm::vec3 normal)
{
	normales.push_back(normal);
}

void PAGvao::addTextCoor(glm::vec2 coordenada)
{
	textCoor.push_back(coordenada);
}

void PAGvao::addTangente(glm::vec3 tangente)
{
	tangentes.push_back(tangente);
}
void PAGvao::addIndice(GLenum modoDibujo, GLuint valor)
{
	switch (modoDibujo)
	{
	case GL_LINES:
		indicesAlambre.push_back(valor);
		break;
	case GL_TRIANGLES:
		indicesSolido.push_back(valor);
		break;
	case GL_POINTS:
		indicesPuntos.push_back(valor);
		break;
	case GL_TRIANGLE_STRIP:
		indicesMalla.push_back(valor);
		break;
	case GL_TRIANGLE_FAN:
		indicesAbanico.push_back(valor);
	default:
		break;
	}


}



void PAGvao::generaArray()
{
	//Generamos el VAO
	glGenVertexArrays(1, &identificador);
	glBindVertexArray(identificador);
	//Generamos el VBO
	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(glm::vec3), ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vboNormales);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormales);
	glBufferData(GL_ARRAY_BUFFER, normales.size() * sizeof(glm::vec3), normales.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(glm::vec3), ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(1);
	glGenBuffers(1, &vboTextCoor);
	glBindBuffer(GL_ARRAY_BUFFER, vboTextCoor);
	glBufferData(GL_ARRAY_BUFFER, textCoor.size() * sizeof(glm::vec2), textCoor.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(glm::vec2), ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(2);
	glGenBuffers(1, &vboTangentes);
	glBindBuffer(GL_ARRAY_BUFFER, vboTangentes);
	glBufferData(GL_ARRAY_BUFFER, tangentes.size() * sizeof(glm::vec3), tangentes.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(3, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(glm::vec3), ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(3);
	//Generamos los IBOs
	glGenBuffers(1, &iboSolido);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboSolido);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesSolido.size(), indicesSolido.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &iboAlambre);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboAlambre);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesAlambre.size(), indicesAlambre.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &iboPuntos);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPuntos);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesPuntos.size(), indicesPuntos.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &iboMalla);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboMalla);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesMalla.size(), indicesMalla.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &iboAbanico);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboAbanico);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesAbanico.size(), indicesAbanico.data(), GL_STATIC_DRAW);
	//Por último, indicamos que el VAO está listo para pintar
	listo = true;
}

void PAGvao::activaArray(GLenum modoDibujo)
{
	//Desactivamos cualquier VAO activo
	glBindVertexArray(0);
	//Activamos el VAO y el VBO
	glBindVertexArray(identificador);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//Activamos el IBO correspondiente
	switch (modoDibujo) {
	case GL_LINES:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboAlambre);
		break;
	case GL_TRIANGLES:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboSolido);
		break;
	case GL_POINTS:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboPuntos);
		break;
	case GL_TRIANGLE_STRIP:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboMalla);
		break;
	case GL_TRIANGLE_FAN:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboAbanico);
		break;
	default:
		break;
	}
}

void PAGvao::pintaArray(GLenum modoDibujo)
{
	//Pintamos utilizando el número de índices correspondiente
	switch (modoDibujo) {
	case GL_LINES:
		glDrawElements(modoDibujo, indicesAlambre.size(), GL_UNSIGNED_INT, NULL);
		break;
	case GL_TRIANGLES:
		glDrawElements(modoDibujo, indicesSolido.size(), GL_UNSIGNED_INT, NULL);
		break;
	case GL_POINTS:
		glDrawElements(modoDibujo, indicesPuntos.size(), GL_UNSIGNED_INT, NULL);
		break;
	case GL_TRIANGLE_STRIP:
		glDrawElements(modoDibujo, indicesMalla.size(), GL_UNSIGNED_INT, NULL);
		break;
	case GL_TRIANGLE_FAN:
		glDrawElements(modoDibujo, indicesAbanico.size(), GL_UNSIGNED_INT, NULL);
		break;
	default:
		break;
	}
}

bool PAGvao::listoParaDibujar()
{
	return listo;
}
