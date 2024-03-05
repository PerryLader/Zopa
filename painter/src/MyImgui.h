#pragma once

#include "Pen.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "global.h"
ImFont* mainfont;
bool TutorialOn = false;
void ImguiInit(GLFWwindow* window )
{
	const char* glsl_version = "#version 130";
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontDefault();
	mainfont = io.Fonts->AddFontFromFileTTF("res/ImguiFonts/HadirSans-8MpeJ.otf",13.5f);
	
	//for exec
	//mainfont = io.Fonts->AddFontFromFileTTF("../../painter/res/ImguiFonts/HadirSans-8MpeJ.otf", 13.5f);
	IM_ASSERT(mainfont != NULL);

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	//ImGui::StyleColorsLight();
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	//src/vendor/text_fonts/freemono.png"
	//, "src/vendor/text_fonts/freemono.meta", WIDTH, HEIGHT);
}
void ImguieSetup()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
}
void ImguieDestroy()
{
	ImGui::PopStyleColor();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void ImguiTutorial() {

	
	ImGui::SetNextWindowPos(ImVec2(800.0f, 500.0f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(900, 500), ImGuiCond_Once);


	ImGui::Begin("Tutorial", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::PushFont(mainfont);

	ImGui::SetWindowFontScale(2.0f);
	ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.8f, 1.0f), "Welcome to the ZOPA tutorial\n\n");
	ImGui::SetWindowFontScale(1.0f);


	ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
		"- In order to draw a shape press CTRL + # and hold the CTRL button in order to control the shape.\n\n"
		"- #   = should be the letter that reprsent the shape(for example - Circle # == C).\n\n"
		"- To return from circle or squre mode just release the CTRL button.\n\n"
		"- To return from Text or Arrow or Matrix mode press the CTRL + # again.\n\n"
		"- Press CTRL + Z to Undo.\n\n"
		"- press CTRL + D to enter delete mode and press again to return from Delete Mode\n"); 	


	ImGui::PopFont();
	ImGui::End();
}
void ImguiMenu()
{
	ImGui::SetNextWindowPos(ImVec2(1720.0f, 170.0f), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::Begin("menu",nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	
	ImGui::SliderFloat("pen width", &pen_width, 2.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::ColorEdit4("pen color", (float*)&pen_color); // Edit 3 floats representing a color
	ImGui::ColorEdit4("Shapes color", (float*)&shape_color); // Edit 3 floats representing a color
	ImGui::SliderInt("fps scale", &maxFPS, 120, 1200);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::Button("Reset")) {
		PenReset();
		Allshapes.Reset();
		mode = Mode::Idle;
		while (!ActionStack.empty()) {
			ActionStack.pop();
		}
	}
	if (ImGui::Button("tutorial")) {
		TutorialOn = !TutorialOn;
	}
	ImGui::End();
}
void ImguiHelper()
{
	std::string helpString;
	std::string modeString;
	switch (mode)
	{
	case Idle:
		helpString = "";
		modeString = "Idle Mode\n";
		break;
	case PenMode:
		helpString = "";
		modeString = "Drawing Mode\n";
		break;
	case SqureMode:
		helpString = 
					 "1) hold CTRL and click mouse's left button to change the location of the squre\n"
					 "2) hold CTRL and scroll mouse's wheel to changethe  size of the squre\n"
			         "3) release CTRL in order to get out of sq Mode\n";
		modeString = "Squre Mode\n";
		break;
	case CircleMode:
		helpString = 
			"1) hold CTRL and click mouse's left button to change the location of the circle\n"
			"2) hold CTRL and scroll mouse's wheel to change the size of the circle\n"
			"3) release CTRL in order to get out of circle Mode\n";
		modeString = "Circle Mode\n";
		break;
	case ArrowMode:
		helpString =
			"1) hold CTRL and click mouse's left button to change the location of the arrow\n"
			"2) hold CTRL and scroll mouse's wheel to change the size of  the arrow\n"
			"3) click mouse's left button to change the direction of the arrow\n"
			"4) press CTRL+A in order to get out of arrow Mode\n";
		modeString = "Arrow Mode\n";
		break;
	case TextMode:
		helpString = 
			"1) hold CTRL and click mouse's left button to change the location of the text.\n"
			"2) hold CTRL and scroll mouse's wheel to change the size of the text.\n"
			"3) type desired text.\n"
			"4) press CTRL+T in order to get out of text Mode\n";
		modeString = "Text Mode\n";
		break;
	case MatrixMode:
		if (currMatrixMode == ColAndRow::Row)
		{
			helpString = 
				"1) hold CTRL and click mouse's left button to change the location of the matrix\n"
				"2) hold CTRL and scroll mouse's wheel to change the size of the matrix\n"
				"3) press the number of desired rows\n"
				"4) press enter in order to change the number of colums\n"
				"5) press CTRL+M in order to get out of matrix Mode\n";
			modeString = "Matrix Mode\n";
		}
		else
		{
			helpString = 
				"1) hold CTRL and click mouse's left button to change the location of the matrix\n"
				"2) hold CTRL and scroll mouse's wheel to change the size of the matrix\n"
				"3) press the number of desired colums\n"
				"4) press backspace in order to change number of rows\n"
				"5) press CTRL+M in order to get out of matrix Mode\n";
			modeString = "Matrix Mode\n";
		}
		
		break;
	case DeleteMode:
		helpString = "1) Click trash icon in order to delete the shape\n";
		modeString = "Delete Mode\n";
		break;
	default:
		break;
	}

	char buffer[1024];
	sprintf_s(buffer, "Current mode is: %s", modeString.c_str());
	std::string finalModeString(buffer);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(800.0f, 100.0f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(900, 200), ImGuiCond_Once);
	ImGui::Begin("Helper", nullptr, ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoResize);
	ImGui::PushFont(mainfont);


	//mode text
	ImGui::SetWindowFontScale(2.0f);
	float textWidth = ImGui::CalcTextSize(finalModeString.c_str()).x;
	float windowWidth = ImGui::GetWindowWidth();
	float centerX = (windowWidth - textWidth) * 0.5f;
	ImGui::SetCursorPosX(centerX);
	ImGui::TextColored(ImVec4(0.1f, 0.1f, 0.4f, 1.0f), finalModeString.c_str());


	//help text
	ImGui::SetWindowFontScale(1.5f);	
	ImGui::SetCursorPosX(10);
	ImGui::TextColored(ImVec4(0.1f, 0.1f, 0.4f, 1.0f), helpString.c_str());
	ImGui::SetWindowFontScale(1.0f);


	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleColor();
	
}
void ImguiEveryFrame()
{
	ImguieSetup();
	ImguiMenu();
	ImguiHelper();
	if (TutorialOn)
	{
		ImguiTutorial();
	}
	ImGui::Render();
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}