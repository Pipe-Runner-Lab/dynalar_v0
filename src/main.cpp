#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "engine/Renderer.h"
#include "engine/core/VertexBufferLayout.h"
#include "engine/core/VertexBuffer.h"
#include "engine/core/Shader.h"
#include "engine/core/Texture.h"


const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	GLFWwindow* mainWindow;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "GLFW initialization failed" << std::endl;
		return -1;
	}

	/* Setup GLFW window property */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set minor version to 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profile to core
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Set forward compatibility to true

	/* Create a windowed mode window and its OpenGL context */
	mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Dynalar V0", NULL, NULL);
	if (!mainWindow)
	{
		std::cout << "GLFW failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); // get actual sizes of the created window

	/* Make the window's context current */
	glfwMakeContextCurrent(mainWindow); // tells openGL which window to use

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	/* Initialize GLEW */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW initialization failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Enable depth test & blending */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	/* Set blending function */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Setup viewport size */
	glViewport(0, 0, bufferWidth, bufferHeight);

	/* Enable vsync : Sync render loop to monitor refresh rate */
	glfwSwapInterval(1);

	/*Triangle triangle = Triangle();
	triangle.move(0.3f, 0, 0);*/
	//TriangleImp tri = TriangleImp();
	Renderer renderer = Renderer();

	GLfloat vertices[4 * (3 + 2)] = {
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // LB
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // RB
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // RT
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f, // LT
	};

	GLuint indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va = VertexArray();
	VertexBuffer vb = VertexBuffer(
		vertices,
		sizeof(vertices)
	);

	VertexBufferLayout layout = VertexBufferLayout();
	layout.Push<float>(3); // vertices
	layout.Push<float>(2); // texture coordinates

	va.AddBuffer(vb, layout);
	IndexBuffer ib = IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));

	Shader shader = Shader("assets/shaders/sample.vert", "assets/shaders/sample.frag");
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.Unbind();

	Texture texture = Texture("assets/images/logo.png");
	texture.Bind();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(mainWindow))
	{
		/* Check for user events */
		glfwPollEvents();

		/* Render here */
		renderer.Clear();

		// INFO: swap buffer should not be called before drawing
		//triangle.draw
		renderer.Draw(va, ib, shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(mainWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}