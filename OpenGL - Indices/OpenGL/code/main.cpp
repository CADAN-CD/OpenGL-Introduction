#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
 
#include "../OpenGL/shaderClass.h"
#include "../OpenGL/VAO.h"
#include "../OpenGL/VBO.h"
#include "../OpenGL/EBO.h"


int main()
{
	// Initialize GLFW
	glfwInit();

	//version of the OpenGL to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//we are using a core profile, that means we only are using the functions that are available in the version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(800, 800, "IndicesOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	
	gladLoadGL();
	
	glViewport(0, 0, 800, 800);




	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.9f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	
	GLuint indices[] =
	{
		0, 3, 5, 
		3, 2, 4,
		5, 4, 1 
	};
	//reads the shader contained in the files default.vert and default.frag and creates a shader program
	Shader shaderProgram("default.vert", "default.frag");
	//declaration of VAO to store the vertices configuration
	//declaration of VBO to store the vertices coordinates in the GPU
	//EBO to store the indices in the GPU
	VAO VAO1;
	//activates the VA01, so we can link the vertices to the VAO
	VAO1.Bind();
	//Generates VertexBuffer objects and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	//EBO avoids repeat the same vertex 
	EBO EBO1(indices, sizeof(indices));
	//unbind to avoid accidentally modifying the VAO and VBO configurations
	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//creates the background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clears the back buffer and asgins the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		//activates the shader program
		shaderProgram.Activate();
		//bind the VAO for openGL to use the configurations stored in it
		VAO1.Bind();
		//function that links the indices and vertices and draws the triangles
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//swaps the back buffer with the front buffer to update the window with the triangle
		glfwSwapBuffers(window);
		//takes care of the events of the window
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}