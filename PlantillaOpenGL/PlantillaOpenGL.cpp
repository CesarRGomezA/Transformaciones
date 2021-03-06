// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include<iostream>

using namespace std;

float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float angulo = 0.0f;


enum Direccion {Izquierda, Derecha, Arriba, Abajo};
Direccion direccionTriangulo = Direccion::Izquierda;
Direccion direccionTrianguloVertical = Direccion::Arriba;

void dibujarTriangulo() {

	//Utilizar matris identidad
	glPushMatrix();
	//Transformacion
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotated(angulo, 1.0f, 1.0f, 1.0f);
	//dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);
	glEnd();

	//soltar la matriz
	glPopMatrix();

}


void dibujar() {
	dibujarTriangulo();

}

void actualizar() {
	if (angulo >= 360)
	{
		angulo = 0.0f;
	}
	angulo += 0.1f;


	if (direccionTriangulo == Direccion::Izquierda)
	{
		if (posicionXTriangulo > -0.79f)
		{
			posicionXTriangulo -= 0.001f;
		}
		else {
			direccionTriangulo = Direccion::Derecha;
		}
	}
	if (direccionTriangulo == Direccion::Derecha) {
		if (posicionXTriangulo < 0.79) {
			posicionXTriangulo += 0.001f;
		}
		else {
			direccionTriangulo = Direccion::Izquierda;
		}
	}
	
	if (direccionTrianguloVertical == Direccion::Abajo)
	{
		if (posicionYTriangulo > -0.79f)
		{
			posicionYTriangulo -= 0.0005f;
		}
		else {
			direccionTrianguloVertical = Direccion::Arriba;
		}
	}
	if (direccionTrianguloVertical == Direccion::Arriba)
	{
		if (posicionYTriangulo < 0.79f)
		{
			posicionYTriangulo += 0.0005f;
		}
		else {
			direccionTrianguloVertical = Direccion::Abajo;
		}
	}
}


int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//Si no se pudo iniciar glfw
	//terminamos ejecución 
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	
	//Si se pudo inciar GLFW
	//Entonces inicializamos la ventana

	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana 
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecer el contexto
	glfwMakeContextCurrent(window);


	//Una vez establecido el contexto
	//Activamos fnciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK)
	{
		cout << glewGetErrorString(errorGlew);

	}


	const GLubyte *versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: "
		<< versionGL;



	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0,1024, 768);
		//Establecer el color de orrado
		glClearColor(0.5, 0.4, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

