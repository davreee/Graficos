#include <iostream>
#include <cstdlib>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Variables que almacenan el color de la escena
float colorComponenteR = 0.3;
float colorComponenteG = 0.6;
float colorComponenteB = 0.9;
float const COMPONENTE_TRANSPARENCIA = 1.0;

//Generamos el cambio que tendrá la componente aleatoriamente en el rango [0.01, 0.05]
float cambioColorAleatorio() {
	return  ((rand() % 5) + 1) * 0.01;
}

//Función que se encarga de gestionar la entrada del usuario con la ruedecilla del ratón
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset < 0) {
		//Baja la ruedecilla
		colorComponenteR -= cambioColorAleatorio();
		colorComponenteG -= cambioColorAleatorio();
		colorComponenteB -= cambioColorAleatorio();
	}
	else if (yoffset > 0)
	{
		//Sube la ruedecilla
		colorComponenteR += cambioColorAleatorio();
		colorComponenteG += cambioColorAleatorio();
		colorComponenteB += cambioColorAleatorio();
	}

	//Truncamos las componentes que se salgan del Rango [0,1]
	//Componente R
	if (colorComponenteR < 0.0 || colorComponenteR > 1.0) {
		colorComponenteR = truncf(colorComponenteR);
	}
	//Componente G
	if (colorComponenteG < 0.0 || colorComponenteG > 1.0) {
		colorComponenteG = truncf(colorComponenteG);
	}
	//Componente B
	if (colorComponenteB < 0.0 || colorComponenteB > 1.0) {
		colorComponenteB = truncf(colorComponenteB);
	}

	//Pintamos del nuevo color
	glClearColor(colorComponenteR, colorComponenteG, colorComponenteB, COMPONENTE_TRANSPARENCIA);

}

int main() {

	if (glfwInit() == GLFW_FALSE) {
		throw std::runtime_error("Error inicializando GLFW");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* ventana;

	ventana = glfwCreateWindow(800, 600, "Practica 0", nullptr, nullptr);

	if (ventana == nullptr) {
		glfwTerminate();
		throw std::runtime_error("Error creando la ventana");
	}
	glfwMakeContextCurrent(ventana);
	glfwSetScrollCallback(ventana, scroll_callback);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwDestroyWindow(ventana);
		ventana = nullptr;
		glfwTerminate();
		throw std::runtime_error("Error inicializando GLEW");
	}

	GLuint shaderProgramID;
	shaderProgramID = glCreateProgram();

	glClearColor(colorComponenteR, colorComponenteG, colorComponenteB, COMPONENTE_TRANSPARENCIA);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(ventana)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(ventana);
	}

	glfwDestroyWindow(ventana);
	ventana = nullptr;
	glfwTerminate();
}