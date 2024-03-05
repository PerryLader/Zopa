#include <imgui.h>
#include <imgui_impl_glfw.h> // GLFW bindings
#include <imgui_impl_opengl3.h> // OpenGL bindings (replace with your rendering API)
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialize GLFW and create a window
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Window with White Background Example", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Modify the background color of ImGui windows
    ImGui::StyleColorsLight(); // Set a light theme (optional)

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create an ImGui window
        ImGui::Begin("Window with White Background");

        // Set the window background color to white
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        // Add content to the window
        ImGui::Text("This is a window with a white background.");

        // Restore the original style after rendering
        ImGui::PopStyleColor();

        ImGui::End();

        // Rendering
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Terminate GLFW and exit
    glfwTerminate();

    return 0;
}
