#ifndef MAIN  
#define MAIN

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

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
#include "text.h"
#include "Texture.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "vendor/stb/stb_image.h"


GLFWwindow* window;
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
	window = glfwCreateWindow(WIDTH, HEIGHT, "ZOOPA", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(-1);
	}
	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);
	ImguiInit(window);

	glEnable(GL_PROGRAM_POINT_SIZE);

	//input callbacks
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, KeyCalBack);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetCharModsCallback(window, KeyCharCalBack);


	glfwSwapInterval(0);
	init_text_rendering("src/vendor/text_fonts/freemono.png"
		, "src/vendor/text_fonts/freemono.meta", WIDTH, HEIGHT);
	
	

	//for exec
	//init_text_rendering("../../painter/src/vendor/text_fonts/freemono.png"
	//, "../../painter/src/vendor/text_fonts/freemono.meta", WIDTH, HEIGHT);
	
}

void Exit(VertexArry* VA, VertexBuffer* VB)
{
	ImguieDestroy();
	for (int i = 0; i < (int)pointesArry.size()-1; i++) {
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
	 
	/*Shader penShader("../../painter/res/shaders/PenshaderV3.0.txt",true);
	Shader ShapeShader("../../painter/res/shaders/ShapeshaderV1.0.txt",false);	
	Shader TextureShader("../../painter/res/shaders/TextureShaderV1.0.txt", false);
	Texture texture("../../painter/res/textures/1214428.png");*/


	//for exec
	Shader penShader("res/shaders/PenshaderV3.0.txt", true);
	Shader ShapeShader("res/shaders/ShapeshaderV1.0.txt", false);	
	Shader TextureShader("res/shaders/TextureShaderV1.0.txt", false);	
	Texture texture("res/textures/1214428.png");
	

	GLuint tex1, tex2;
	
	
	double lastTime = 0.0;
	double xpos, ypos;
	while (!glfwWindowShouldClose(window))
	{				
		double time = glfwGetTime();
		double deltaTime = time - lastTime;
		if (deltaTime >= 1.0 / maxFPS)
		{
			lastTime = time;
			if (mode==Mode::PenMode) {
				
				glfwGetCursorPos(window, &xpos, &ypos);
				addPoint(xpos, ypos);
			}
			VA[0].UnBind();
			
			renderer.Clear();
			renderer.SetBackGroundColor(1.0f, 1.0f, 1.0f, 1.0f);
			renderer.DrawPen(VA, &penShader, VB);
			renderer.DrawShapes(&ShapeShader); 	
			draw_texts();						

			if (mode == Mode::DeleteMode)
			{

				renderer.DrawDeleteButtons(&TextureShader,&texture);
			}

			glfwPollEvents();
			ImguiEveryFrame();
			glfwSwapBuffers(window);
		}
	}
	Exit(VA, VB);
	
	return EXIT_SUCCESS;
}

#endif 