#pragma once

#include "Pen.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
void ImguiInit()
{
	const char* glsl_version = "#version 130";
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

}
void ImguieSetup()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void ImguieDestroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void ImguiMenu()
{
	ImGui::Begin("menu");
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SliderFloat("pen width", &pen_width, 2.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::ColorEdit4("pen color", (float*)&pen_color); // Edit 3 floats representing a color
	ImGui::SliderInt("fps scale", &maxFPS, 120, 1200);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::Button("Reset")) {
		PenReset();
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}