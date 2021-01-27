#include "PAGmodelo.h"
PAGmodelo::PAGmodelo(tipoModelo tipo, glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho, std::string nombreNormalMap, float altoMap, float anchoMap) :
	modoVisualizacion(GL_TRIANGLES),
	material(colorAmbiente, colorDifuso, colorEspecular, brillo),
	instancias(),
	textura(nombreTextura, alto, ancho),
	normalMap(nombreNormalMap, altoMap, anchoMap),
	usaNormalMap(true)
{
	vao = new PAGvao();
	switch (tipo)
	{
	case PAGmodelo::PAG_TRIANGULO:

		//Insertamos los vertices
		vao->addVertice(glm::vec3(-2, -2, 0));
		vao->addVertice(glm::vec3(2, -2, 0));
		vao->addVertice(glm::vec3(2, 2, 0));
		vao->addNormal(glm::vec3(0, 0, 1));
		vao->addNormal(glm::vec3(0, 0, 1));
		vao->addNormal(glm::vec3(0, 0, 1));
		//Insertamos los indices para cada modo de visualización
		vao->addIndice(GL_TRIANGLES, 0);
		vao->addIndice(GL_TRIANGLES, 1);
		vao->addIndice(GL_TRIANGLES, 2);

		vao->addIndice(GL_LINES, 0);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 0);

		vao->addIndice(GL_POINTS, 0);
		vao->addIndice(GL_POINTS, 1);
		vao->addIndice(GL_POINTS, 2);

		break;
	case PAGmodelo::PAG_CUADRADO:
		//Insertamos los vertices
		//0
		vao->addVertice(glm::vec3(-6, -1, -6));
		vao->addTextCoor(glm::vec2(1, 0));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTangente(glm::vec3(1, 0, 0));

		//1
		vao->addVertice(glm::vec3(6, -1, -6));
		vao->addTextCoor(glm::vec2(1, 1));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTangente(glm::vec3(1, 0, 0));

		//2
		vao->addVertice(glm::vec3(6, -1, 6));
		vao->addTextCoor(glm::vec2(0, 1));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTangente(glm::vec3(1, 0, 0));

		//3
		vao->addVertice(glm::vec3(-6, -1, 6));
		vao->addTextCoor(glm::vec2(0, 0));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTangente(glm::vec3(1, 0, 0));

		//Insertamos los indices para cada modo de visualización
		vao->addIndice(GL_TRIANGLES, 0);
		vao->addIndice(GL_TRIANGLES, 1);
		vao->addIndice(GL_TRIANGLES, 2);
		vao->addIndice(GL_TRIANGLES, 2);
		vao->addIndice(GL_TRIANGLES, 3);
		vao->addIndice(GL_TRIANGLES, 0);

		vao->addIndice(GL_LINES, 0);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 3);
		vao->addIndice(GL_LINES, 3);
		vao->addIndice(GL_LINES, 0);

		vao->addIndice(GL_POINTS, 0);
		vao->addIndice(GL_POINTS, 1);
		vao->addIndice(GL_POINTS, 2);
		vao->addIndice(GL_POINTS, 3);


		break;
	case PAGmodelo::PAG_TETRAEDRO:
		vao->addVertice(glm::vec3(0, 0, 0));
		vao->addVertice(glm::vec3(0, 0, 2));
		vao->addVertice(glm::vec3(2, 0, 0));
		vao->addVertice(glm::vec3(0, 2, 0));

		vao->addIndice(GL_TRIANGLES, 0);
		vao->addIndice(GL_TRIANGLES, 1);
		vao->addIndice(GL_TRIANGLES, 2);
		vao->addIndice(GL_TRIANGLES, 0);
		vao->addIndice(GL_TRIANGLES, 1);
		vao->addIndice(GL_TRIANGLES, 3);
		vao->addIndice(GL_TRIANGLES, 0);
		vao->addIndice(GL_TRIANGLES, 2);
		vao->addIndice(GL_TRIANGLES, 3);

		vao->addIndice(GL_LINES, 0);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 0);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 0);
		vao->addIndice(GL_LINES, 3);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 1);
		vao->addIndice(GL_LINES, 3);
		vao->addIndice(GL_LINES, 2);
		vao->addIndice(GL_LINES, 3);

		vao->addIndice(GL_POINTS, 0);
		vao->addIndice(GL_POINTS, 1);
		vao->addIndice(GL_POINTS, 2);
		vao->addIndice(GL_POINTS, 3);

		break;
	case PAGmodelo::PAG_CUBO:
		//0
		vao->addVertice(glm::vec3(-1, -1, 1));
		vao->addNormal(glm::vec3(0, 0, 1));
		vao->addTextCoor(glm::vec2(.25, .25));
		vao->addTangente(glm::vec3(1, 0, 0));
		//1
		vao->addVertice(glm::vec3(1, -1, 1));
		vao->addNormal(glm::vec3(0, 0, 1));
		vao->addTextCoor(glm::vec2(.5, .25));
		vao->addTangente(glm::vec3(1, 0, 0));

		//2
		vao->addVertice(glm::vec3(-1, 1, 1));
		vao->addNormal(glm::vec3(0, 0, 1));
		vao->addTextCoor(glm::vec2(.25, .5));
		vao->addTangente(glm::vec3(1, 0, 0));

		//3
		vao->addVertice(glm::vec3(1, 1, 1));
		vao->addNormal(glm::vec3(0, 0, 1));
		vao->addTextCoor(glm::vec2(.5, .5));
		vao->addTangente(glm::vec3(1, 0, 0));

		vao->addIndice(GL_TRIANGLES, 0);
		vao->addIndice(GL_TRIANGLES, 1);
		vao->addIndice(GL_TRIANGLES, 2);
		vao->addIndice(GL_TRIANGLES, 2);
		vao->addIndice(GL_TRIANGLES, 1);
		vao->addIndice(GL_TRIANGLES, 3);

		//4
		vao->addVertice(glm::vec3(1, 1, 1));
		vao->addNormal(glm::vec3(1, 0, 0));
		vao->addTextCoor(glm::vec2(.5, .5));
		vao->addTangente(glm::vec3(0, 0, -1));

		//5
		vao->addVertice(glm::vec3(1, -1, 1));
		vao->addNormal(glm::vec3(1, 0, 0));
		vao->addTextCoor(glm::vec2(.5, .25));
		vao->addTangente(glm::vec3(0, 0, -1));

		//6
		vao->addVertice(glm::vec3(1, -1, -1));
		vao->addNormal(glm::vec3(1, 0, 0));
		vao->addTextCoor(glm::vec2(.75, .25));
		vao->addTangente(glm::vec3(0, 0, -1));

		//7
		vao->addVertice(glm::vec3(1, 1, -1));
		vao->addNormal(glm::vec3(1, 0, 0));
		vao->addTextCoor(glm::vec2(.75, .5));
		vao->addTangente(glm::vec3(0, 0, -1));

		vao->addIndice(GL_TRIANGLES, 4);
		vao->addIndice(GL_TRIANGLES, 5);
		vao->addIndice(GL_TRIANGLES, 6);
		vao->addIndice(GL_TRIANGLES, 6);
		vao->addIndice(GL_TRIANGLES, 7);
		vao->addIndice(GL_TRIANGLES, 4);

		//8
		vao->addVertice(glm::vec3(-1, 1, 1));
		vao->addNormal(glm::vec3(-1, 0, 0));
		vao->addTextCoor(glm::vec2(0, .5));
		vao->addTangente(glm::vec3(0, 0, 1));

		//9
		vao->addVertice(glm::vec3(-1, -1, 1));
		vao->addNormal(glm::vec3(-1, 0, 0));
		vao->addTextCoor(glm::vec2(0, .25));
		vao->addTangente(glm::vec3(0, 0, 1));

		//10
		vao->addVertice(glm::vec3(-1, -1, -1));
		vao->addNormal(glm::vec3(-1, 0, 0));
		vao->addTextCoor(glm::vec2(0.25, .25));
		vao->addTangente(glm::vec3(0, 0, 1));

		//11
		vao->addVertice(glm::vec3(-1, 1, -1));
		vao->addNormal(glm::vec3(-1, 0, 0));
		vao->addTextCoor(glm::vec2(.25, .5));
		vao->addTangente(glm::vec3(0, 0, 1));

		vao->addIndice(GL_TRIANGLES, 8);
		vao->addIndice(GL_TRIANGLES, 9);
		vao->addIndice(GL_TRIANGLES, 10);
		vao->addIndice(GL_TRIANGLES, 10);
		vao->addIndice(GL_TRIANGLES, 11);
		vao->addIndice(GL_TRIANGLES, 8);

		//12
		vao->addVertice(glm::vec3(-1, 1, -1));
		vao->addNormal(glm::vec3(0, 0, -1));
		vao->addTextCoor(glm::vec2(.75, .5));
		vao->addTangente(glm::vec3(-1, 0, 0));

		//13
		vao->addVertice(glm::vec3(-1, -1, -1));
		vao->addNormal(glm::vec3(0, 0, -1));
		vao->addTextCoor(glm::vec2(.75, .25));
		vao->addTangente(glm::vec3(-1, 0, 0));

		//14
		vao->addVertice(glm::vec3(1, -1, -1));
		vao->addNormal(glm::vec3(0, 0, -1));
		vao->addTextCoor(glm::vec2(1, .25));
		vao->addTangente(glm::vec3(-1, 0, 0));

		//15
		vao->addVertice(glm::vec3(1, 1, -1));
		vao->addNormal(glm::vec3(0, 0, -1));
		vao->addTextCoor(glm::vec2(1, .5));
		vao->addTangente(glm::vec3(-1, 0, 0));

		vao->addIndice(GL_TRIANGLES, 12);
		vao->addIndice(GL_TRIANGLES, 13);
		vao->addIndice(GL_TRIANGLES, 14);
		vao->addIndice(GL_TRIANGLES, 14);
		vao->addIndice(GL_TRIANGLES, 15);
		vao->addIndice(GL_TRIANGLES, 12);

		//16
		vao->addVertice(glm::vec3(-1, -1, -1));
		vao->addNormal(glm::vec3(0, -1, 0));
		vao->addTextCoor(glm::vec2(.25, .25));
		vao->addTangente(glm::vec3(1, 0, 0));

		//17
		vao->addVertice(glm::vec3(-1, -1, 1));
		vao->addNormal(glm::vec3(0, -1, 0));
		vao->addTextCoor(glm::vec2(.25, .0));
		vao->addTangente(glm::vec3(1, 0, 0));

		//18
		vao->addVertice(glm::vec3(1, -1, 1));
		vao->addNormal(glm::vec3(0, -1, 0));
		vao->addTextCoor(glm::vec2(.5, 0));
		vao->addTangente(glm::vec3(1, 0, 0));

		//19
		vao->addVertice(glm::vec3(1, -1, -1));
		vao->addNormal(glm::vec3(0, -1, 0));
		vao->addTextCoor(glm::vec2(.5, .25));
		vao->addTangente(glm::vec3(1, 0, 0));

		vao->addIndice(GL_TRIANGLES, 16);
		vao->addIndice(GL_TRIANGLES, 17);
		vao->addIndice(GL_TRIANGLES, 18);
		vao->addIndice(GL_TRIANGLES, 18);
		vao->addIndice(GL_TRIANGLES, 19);
		vao->addIndice(GL_TRIANGLES, 16);

		//20
		vao->addVertice(glm::vec3(-1, 1, -1));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTextCoor(glm::vec2(.25, .75));
		vao->addTangente(glm::vec3(1, 0, 0));

		//21
		vao->addVertice(glm::vec3(-1, 1, 1));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTextCoor(glm::vec2(.25, .5));
		vao->addTangente(glm::vec3(1, 0, 0));

		//22
		vao->addVertice(glm::vec3(1, 1, 1));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTextCoor(glm::vec2(.5, .5));
		vao->addTangente(glm::vec3(1, 0, 0));

		//23
		vao->addVertice(glm::vec3(1, 1, -1));
		vao->addNormal(glm::vec3(0, 1, 0));
		vao->addTextCoor(glm::vec2(.5, .75));
		vao->addTangente(glm::vec3(1, 0, 0));

		vao->addIndice(GL_TRIANGLES, 20);
		vao->addIndice(GL_TRIANGLES, 21);
		vao->addIndice(GL_TRIANGLES, 22);
		vao->addIndice(GL_TRIANGLES, 22);
		vao->addIndice(GL_TRIANGLES, 23);
		vao->addIndice(GL_TRIANGLES, 20);


		break;

	default:
		break;
	}

	//Por defecto añadimos una instancia a cualquier modelo para que al menos haya una de ellas en la escena
	addInstancia();
}

PAGmodelo::PAGmodelo(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normales, std::vector<glm::vec2>& coordenadasTextura, std::vector<GLuint> indices, glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, GLfloat brillo, std::string nombreTextura, float alto, float ancho) :
	modoVisualizacion(GL_TRIANGLES),
	material(colorAmbiente, colorDifuso, colorEspecular, brillo),
	instancias(),
	textura(nombreTextura, alto, ancho),
	normalMap(),
	usaNormalMap(false)
{
	vao = new PAGvao();
	for (int i = 0; i < vertices.size(); i++) {
		vao->addVertice(vertices.at(i));
		vao->addNormal(normales.at(i));
		vao->addTextCoor(coordenadasTextura.at(i));
	}

	for (int i = 0; i < indices.size(); i++) {
		vao->addIndice(GL_TRIANGLES, indices.at(i));
	}

	addInstancia();

}

PAGmodelo::~PAGmodelo()
{
	delete vao;
}

void PAGmodelo::pintate()
{
	//Si el vao no está listo para dibujar, lo generamos
	if (!vao->listoParaDibujar()) {
		vao->generaArray();
	}

	//Lo activamos y lo pintamos
	vao->activaArray(modoVisualizacion);
	textura.activarTextura();
	if (usaNormalMap)
		normalMap.activarNormalMap();
	vao->pintaArray(modoVisualizacion);

}

void PAGmodelo::setmodoVisualizacion(GLenum modoVisualizacion)
{
	this->modoVisualizacion = modoVisualizacion;
}

GLenum PAGmodelo::getmodoVisualizacion()
{
	return modoVisualizacion;
}

glm::vec3 PAGmodelo::getColorAmbiente()
{
	return material.getColorAmbiente();
}

glm::vec3 PAGmodelo::getColorDifuso()
{
	return material.getColorDifuso();
}

glm::vec3 PAGmodelo::getColorEspecular()
{
	return material.getColorEspecular();
}

GLfloat PAGmodelo::getShininess()
{
	return material.getShininess();
}

bool PAGmodelo::getUsaNormalMap()
{
	return usaNormalMap;
}

void PAGmodelo::addInstancia()
{
	instancias.push_back(PAGinstancia());
}

void PAGmodelo::trasladarInstancia(int numInstancia, glm::vec3 traslacion)
{
	if (numInstancia < 0 || numInstancia > instancias.size())
		throw std::out_of_range("PAGmodelo::trasladarInstancia: número de instancia no válido.");

	instancias[numInstancia].trasladar(traslacion);
}

void PAGmodelo::escalarInstancia(int numInstancia, glm::vec3 escalado)
{
	if (numInstancia < 0 || numInstancia > instancias.size())
		throw std::out_of_range("PAGmodelo::escalarInstancia: número de instancia no válido.");

	instancias[numInstancia].escalar(escalado);

}

void PAGmodelo::rotarInstanciaX(int numInstancia, float grados)
{
	if (numInstancia < 0 || numInstancia > instancias.size())
		throw std::out_of_range("PAGmodelo::rotarInstanciaX: número de instancia no válido.");

	instancias[numInstancia].rotarX(grados);

}

void PAGmodelo::rotarInstanciaY(int numInstancia, float grados)
{
	if (numInstancia < 0 || numInstancia > instancias.size())
		throw std::out_of_range("PAGmodelo::rotarInstanciaY: número de instancia no válido.");

	instancias[numInstancia].rotarY(grados);

}

void PAGmodelo::rotarInstanciaZ(int numInstancia, float grados)
{
	if (numInstancia < 0 || numInstancia > instancias.size())
		throw std::out_of_range("PAGmodelo::rotarInstanciaZ: número de instancia no válido.");

	instancias[numInstancia].rotarZ(grados);

}

std::vector<glm::mat4>* PAGmodelo::obtenerInstancias()
{
	std::vector<glm::mat4>* matricesModelado = new std::vector<glm::mat4>();
	for (int i = 0; i < instancias.size(); i++) {
		matricesModelado->push_back(instancias[i].matrizModelado(centroModelo));
	}
	return matricesModelado;
}


