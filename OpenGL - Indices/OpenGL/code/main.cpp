#include<iostream>;
#include<glad/glad.h>
#include<GLFW/glfw3.h>
/* in all package the vertex shader is receiving the vertices and 
gives them directly to the screen. the fragment shader paints all
pixels with the same color/*/
const char* vertexShaderSource = "#version 330 core\n"
//declaration a vect(x,y,z) aPos(name of the variable)+location 
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
//gl position is a obligatory variable and defines the final position of the vertices
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
//declares the output color 
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
//gives the color of the triangle
"   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n\0";

int main() {
	//iniatilize GLFW
	glfwInit();
	// Tell which version of openGL are we using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tell OpenGLFW we are using the CORE Profile 
	//so that means w only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//the vertices
	GLfloat vertices[] =
	{
		//we declarate the coordinates
		-0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,0.0f
	};

	//this one creates a window with his w,h,name, full screan, and ??
	GLFWwindow * window = glfwCreateWindow(800,800, "OpenGl", NULL, NULL);
	// Error check if the window failed to be created
	if (window == NULL) {
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD to configurate OpenGL
	gladLoadGL();
	//The coordenates  and size of the viewport x=0 y=0, to x=800, y =800
	glViewport(0, 0, 800, 800);
	
	/*VERTEXSHADER: Identifies the vetice position in screen
	* and transforms the coordinates 
	*/
	/*create the vertex shader object and get its reference
	we specify the type of shader that we want*/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*
	* in this case we are using 1 chain for the shading, then we point the 
	* source code
	*/
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Reference value
	glCompileShader(vertexShader);
	
	/* FRAGMENT SHADER: Determinates the final color of the pixel*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compile the Vertex Shader into machine code

	
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//we delete the vertex and fragment shader because is already in the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	
	GLuint VAO, VBO;
	// VAO: contains the definition of the data, like how much floats for vetice
	//it generates the IDs but for now they'll not be used
	glGenBuffers(1, &VBO);
	//glBindBuffer: declarates a buffer with a certain ID to use it: type-buffer-id
	//arrayBuffer: contains vertices data- position color, normals, etc
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*specify the type, the size, and the data, the use of the data -
	 The data store contents will be modified once and used
	 many times as the source
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//GLUint VBO is a memory buffer that stores the vertices data in the GPU 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// for now all configuration will be stored inside this VAO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// it helps to comunicate the vertexShader from the outside
	/*position, 3 components x, y, z, type of the values, not notmalice
	each vertice ocupies 3 floats, and starts in the byte 0 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//uses the atribute above
	glEnableVertexAttribArray(0);
	//unpairs the VBO with GL-ARRAY-BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Stops using the glBindVertexArray
	glBindVertexArray(0);




	//Color of the bakcground 
	glClearColor(0.09f, 0.13f, 0.17f, 1.0f);
	//cleands the back buffer and assigns the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	//swaps the back buffer with the front buffer
	glfwSwapBuffers(window);


	//Main While loop to allow the window to be showed while we dont close it 
	while (!glfwWindowShouldClose(window)) {
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//the function specifies the primitive that is going to be drawn
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//we need to be sure to change the buffers 
		glfwSwapBuffers(window);

		//taes care of all GLFW events
		glfwPollEvents();
	}
	//deletes all the objects we created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);



	//deletes window before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}