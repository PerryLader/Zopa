#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <stack>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))



void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

enum Action {
    PenLine,    // 0
    Shape,  // 1
};
const GLuint WIDTH = 1920, HEIGHT = 1080;
static GLFWwindow* window;
extern int maxFPS;
extern std::stack<Action> ActionStack;