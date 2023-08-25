#ifndef MAIN  
#define MAIN

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "Pen.h"
#include "MyImgui.h"
#include "global.h"
#include "KeyBoardInput.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"





void Init()
{
	// Init GLFW
	if (!glfwInit())
		exit(-1);
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "painter CTRL", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, ScrollCallback);
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(-1);
	}
	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);
	ImguiInit();

	glEnable(GL_PROGRAM_POINT_SIZE);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, KeyCalBack);
	glfwSwapInterval(0);

}

void Exit(VertexArry* VA, VertexBuffer* VB)
{
	ImguieDestroy();
	for (int i = 0; i < CURR_NUM_LINES; i++) {
		glDeleteVertexArrays(1, &VA[i].m_RendererID);
		glDeleteBuffers(1, &VB[i].m_RendererID);
	}
	glfwTerminate();
}

int main()
{
	
	Init();
	VertexArry VA[MAX_LINESS];
	VertexBuffer VB[MAX_LINESS];
	Renderer renderer;
	Shader penShader("res/shaders/PenshaderV3.0.txt",true);


	Shader ShapeShader("res/shaders/ShapeshaderV1.0.txt",false);
	ShapeShader.Bind();

	bool running = true;
	double lastTime = 0.0;
	while (!glfwWindowShouldClose(window))
	{				
		double time = glfwGetTime();
		double deltaTime = time - lastTime;
		if (deltaTime >= 1.0 / maxFPS)
		{
			lastTime = time;
			if (moving) {
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				addPoint(xpos, ypos);
			}
			VA[0].UnBind();
			ImguieSetup();
			renderer.Clear();
			renderer.SetBackGroundColor(1.0f, 1.0f, 1.0f, 1.0f);
			renderer.DrawPen(VA, &penShader, VB);
			renderer.DrawShapes(&ShapeShader);
			glfwPollEvents();
			ImguiMenu();
			glfwSwapBuffers(window);
		}
	}
	Exit(VA, VB);
	
	return EXIT_SUCCESS;
}

#endif 