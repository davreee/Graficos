#include <iostream>
#include <cstdlib>
#include <string>
// - IMPORTANTE: El include de Glew debe llamarse siempre ANTES de llamar al de GLFW.

#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include "PagRenderer.h"

//Función que se encarga de gestionar la entrada del usuario con la ruedecilla del ratón
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	PAGrenderer::getInstancia()->callbackScroll(xoffset, yoffset);
}

GLfloat vertices[] = { -.5,-.5,0,
					  .5,-.5,0,
					   0,.5,0 };

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

	ventana = glfwCreateWindow(800, 600, "Practica 3", nullptr, nullptr);
	PAGrenderer::getInstancia()->setViewport(0, 0, 800, 600);

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
	
	std::string nombreShader = "pr03";
	try
	{
		//Creamos el Shader Program
		PAGrenderer::getInstancia()->addShaderProgram(nombreShader);
		//Si la creación del shader es correcta añadimos la información del triángulo. En caso contrario, solo pintamos el fondo
		GLuint miVBA = 0;
		glGenVertexArrays(1, &miVBA);
		glBindVertexArray(miVBA);
		GLuint miVBO = 0;
		glGenBuffers(1, &miVBO);
		glBindBuffer(GL_ARRAY_BUFFER, miVBO);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(0);
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << std::endl;
	}


	glfwSetScrollCallback(ventana, scroll_callback);
	PAGrenderer::getInstancia()->rellenarFondo();
	PAGrenderer::getInstancia()->activarZBuffer();

	while (!glfwWindowShouldClose(ventana)) {
		PAGrenderer::getInstancia()->refrescaVentana();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(ventana);
	}

	glfwDestroyWindow(ventana);
	ventana = nullptr;
	glfwTerminate();
}