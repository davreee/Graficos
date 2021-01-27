#include <iostream>
#include <cstdlib>
#include <string>
// - IMPORTANTE: El include de Glew debe llamarse siempre ANTES de llamar al de GLFW.
#include <vector>
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include "PagRenderer.h"
#include "PAGstatus.h"
#include "OBJ_Loader.h"
#include "PAGmodeloRevolucion.h"
//Función que se encarga de gestionar la entrada del usuario con la ruedecilla del ratón

//Variable que nos distingue si el modelo de triángulo está activo
int camaraActiva;
double sensibilidad = 0.05;
PAGstatus estado;
glm::vec3 colorAmbiente(1.0f, 0.5f, 0.31f);
glm::vec3 colorDifuso(.5f, 0.5f, 0.31f);
glm::vec3 colorEspecular(1.0f, 1.0f, 1.0f);
GLfloat brillo(250);
std::string nombreShaderLuzAmbiente("luzAmbiente");
std::string nombreShaderLuzPuntual("luzPuntual");
std::string nombreShaderLuzSpot("luzSpot");
std::string nombreObj("vaca.obj");
glm::vec3 intensidadDifusa(0.6, 0.6, 0.6);
glm::vec3 intensidadEspecular(1, 1, 1);
glm::vec3 posicionLuzPuntual(0, 2, 0);
glm::vec3 direccionLuzDireccional(1, 0, 0);
glm::vec3 direccionLuzSpot(0, -1, 0);
glm::vec3 posicionLuzSpot(0, 2, -2);
GLfloat apertura(20);
std::vector<glm::vec3> verticesOBJ;
std::vector<glm::vec3> normalesOBJ;
std::vector<glm::vec2> texCoordOBJ;
std::vector<GLuint> indicesOBJ;
int idCubo = 1;
int idVaca = 2;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (estado.getBotonIzqPulsado()) {
		PAGrenderer::getInstancia()->moverCamara(estado.getModoMovimiento(), yoffset, 0);
	}
	else if (!estado.getBotonIzqPulsado() && estado.getModoMovimiento() == PAGvalores::PAGtipoMovimiento::PAG_NINGUNO) {
		if (yoffset < 0) {
			//Baja la ruedecilla
			PAGrenderer::getInstancia()->cambioColorFondo(0);
		}
		else if (yoffset > 0)
		{
			//Sube la ruedecilla
			PAGrenderer::getInstancia()->cambioColorFondo(1);
		}
	}
	PAGrenderer::getInstancia()->refrescaVentana();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (estado.getBotonIzqPulsado() && estado.getModoMovimiento() != PAGvalores::PAGtipoMovimiento::PAG_NINGUNO) {
		double x;
		double y;
		double xoffset;
		double yoffset;
		estado.getPosRaton(x, y);
		xoffset = (xpos - x) * sensibilidad;
		yoffset = (y - ypos) * sensibilidad;

		PAGrenderer::getInstancia()->moverCamara(estado.getModoMovimiento(), xoffset, yoffset);
	}


	estado.setPosRaton(xpos, ypos);
	PAGrenderer::getInstancia()->refrescaVentana();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		estado.setBotonIzqPulsado(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		estado.setBotonIzqPulsado(false);
	}
}

//Función que se encarga de gestionar la entrada del usuario con las teclas
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->activarAnimacion();
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->rotarInstanciaX(idCubo, 0, 45);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->rotarInstanciaY(idCubo, 0, 45);
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->rotarInstanciaZ(idCubo, 0, 45);
	}

	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->escalarInstancia(idCubo, 0, glm::vec3(2, 1, 1));
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->escalarInstancia(idCubo, 0, glm::vec3(.5, 1, 1));
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(0, 0, -1));
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(-1, 0, 0));
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(0, 0, 1));
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(1, 0, 0));
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(0, 1, 0));
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(0, -1, 0));
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		switch (camaraActiva) {
		case 0:
			PAGrenderer::getInstancia()->vistaAlzado();
			std::cout << "Vista Alzado" << std::endl;
			camaraActiva++;
			break;
		case 1:
			PAGrenderer::getInstancia()->vistaPlanta();
			std::cout << "Vista Planta" << std::endl;
			camaraActiva++;
			break;
		case 2:
			PAGrenderer::getInstancia()->vistaPerfil();
			std::cout << "Vista Perfil" << std::endl;
			camaraActiva++;
			break;
		case 3:
			PAGrenderer::getInstancia()->vistaDiagonal();
			std::cout << "Vista Diagonal" << std::endl;
			camaraActiva = 0;
			break;
		default:
			break;
		}
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_PAN);
		std::cout << "Movimientos de Pan Activado" << std::endl;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_TILT);
		std::cout << "Movimientos de Tilt Activado" << std::endl;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_TRUCK);
		std::cout << "Movimientos de Truck/Dolly Activado" << std::endl;
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_BOOM);
		std::cout << "Movimientos de Boom Activado" << std::endl;
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_ORBIT);
		std::cout << "Movimientos de Orbit Activado" << std::endl;
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_ZOOM);
		std::cout << "Movimiento de Zoom activado" << std::endl;
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		estado.setModoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_NINGUNO);
		std::cout << "Movimientos de cámara desactivados" << std::endl;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->activarLuzPuntual();
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		PAGrenderer::getInstancia()->activarLuzSpot();
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (sensibilidad < 0.50) {
			sensibilidad += 0.025;
			std::cout << sensibilidad;
			std::cout << "Sensibilidad aumentada" << std::endl;
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (sensibilidad >= 0.05) {
			sensibilidad -= 0.025;
			std::cout << sensibilidad;
			std::cout << "Sensibilidad disminuidas" << std::endl;
		}
	}

	PAGrenderer::getInstancia()->refrescaVentana();
}

bool cargarObjeto(std::string nombreObjeto) {
	objl::Loader Loader;
	// Load .obj File
	bool loadout = Loader.LoadFile(nombreObjeto);

	// Check to see if it loaded

	// If so continue
	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream file("salidaObj.txt");

		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];

			// Print Mesh Name
			file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

			// Print Vertices
			file << "Vertices:\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				verticesOBJ.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
				normalesOBJ.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
				texCoordOBJ.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
			}

			// Print Indices
			file << "Indices:\n";

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				indicesOBJ.push_back(curMesh.Indices[j]);
				indicesOBJ.push_back(curMesh.Indices[j + 1]);
				indicesOBJ.push_back(curMesh.Indices[j + 2]);
			}

		}

		// Close File
		file.close();
		return true;
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();

		return false;
	}
}

int main() {

	/**	Inicializamos GLFW y comprobamos si ha habido errores durante
		dicho proceso, en cuyo caso, lanzamos una excepci�n.
	*/
	if (glfwInit() == GLFW_FALSE) {
		throw std::runtime_error("Error inicializando GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* ventana;

	ventana = glfwCreateWindow(1024, 1024, "Practica 6", nullptr, nullptr);
	PAGrenderer::getInstancia()->setViewport(0, 0, 1024, 1024);

	if (ventana == nullptr) {
		glfwTerminate();
		throw std::runtime_error("Error creando la ventana");
	}
	glfwMakeContextCurrent(ventana);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwDestroyWindow(ventana);
		ventana = nullptr;
		glfwTerminate();
		throw std::runtime_error("Error inicializando GLEW");
	}


	try
	{
		//Creamos el Shader Program
		PAGrenderer::getInstancia()->crearShaders();
		PAGrenderer::getInstancia()->addLuzAmbiente(glm::vec3(.1, .1, .1));
		PAGrenderer::getInstancia()->addLuzPuntual(intensidadDifusa, intensidadEspecular, posicionLuzPuntual);
		PAGrenderer::getInstancia()->addLuzSpot(intensidadDifusa, intensidadEspecular, posicionLuzSpot, direccionLuzSpot, apertura);
		//Si la creación del shader es correcta añadimos la información del triángulo. En caso contrario, solo pintamos el fondo
		PAGrenderer::getInstancia()->vistaDiagonal();
		camaraActiva = 0;
		PAGrenderer::getInstancia()->addModelo(PAGmodelo::PAG_CUBO, colorAmbiente, colorDifuso, colorEspecular, brillo, "dice_texture.png", 512, 512, "diceNormalMap.png", 512, 512);
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 0, glm::vec3(0, 0, -3));
		PAGrenderer::getInstancia()->addInstancia(idCubo);
		PAGrenderer::getInstancia()->trasladarInstancia(idCubo, 1, glm::vec3(0, 0, 3));
		PAGrenderer::getInstancia()->rotarInstanciaX(idCubo, 1, 45);
		PAGrenderer::getInstancia()->rotarInstanciaZ(idCubo, 1, 45);
		PAGrenderer::getInstancia()->escalarInstancia(idCubo, 1, glm::vec3(1, 2, 1));
		if (cargarObjeto("vaca.obj")) {
			PAGrenderer::getInstancia()->addModelo(verticesOBJ, normalesOBJ, texCoordOBJ, indicesOBJ, colorAmbiente, colorDifuso, colorEspecular, brillo, "spot_texture.png", 1024, 1024);
			PAGrenderer::getInstancia()->trasladarInstancia(idVaca, 0, glm::vec3(-3, 0.46, 0));
			PAGrenderer::getInstancia()->rotarInstanciaX(idVaca, 0, 90);
			PAGrenderer::getInstancia()->rotarInstanciaY(idVaca, 0, 180);
			PAGrenderer::getInstancia()->escalarInstancia(idVaca, 0, glm::vec3(2, 2, 2));
		}
		estado = PAGstatus();

		
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}

	glfwSetScrollCallback(ventana, scroll_callback);
	glfwSetKeyCallback(ventana, key_callback);
	glfwSetMouseButtonCallback(ventana, mouse_button_callback);
	glfwSetCursorPosCallback(ventana, mouse_callback);
	PAGrenderer::getInstancia()->rellenarFondo();
	PAGrenderer::getInstancia()->activarZBuffer();
	PAGrenderer::getInstancia()->activarSizePoint();
	PAGrenderer::getInstancia()->activarBlending();
	PAGrenderer::getInstancia()->activarSaltoPrimitiva();
	while (!glfwWindowShouldClose(ventana)) {
		PAGrenderer::getInstancia()->refrescaVentana();
		glfwPollEvents();
		glfwSwapBuffers(ventana);
	}

	glfwDestroyWindow(ventana);
	ventana = nullptr;
	glfwTerminate();
}