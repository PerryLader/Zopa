#pragma once
#ifndef GLOBAL
#define GLOBAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <stack>
#include <cstdio>

#include "vendor/glm/glm.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))



void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

enum Action {
    AddedPenLine,    // 0
    AddedSqure,  // 1
    AddedCircle,
    AddedArrow,
    AddedText,
    AddedMatrix,

    DeletedPen,
    DeletedSqure,
    DeletedCircle,
    DeletedArrow,
    DeletedMatrix,
    DeletedText
};

enum ShapeType {
    TypePen,    // 0
    TypeSqure,  // 1
    TypeCircle,
    TypeArrow,
    TypeText,
    TypeMatrix,
    TypeShape
};

enum Mode {
    Idle,
    PenMode,    
    SqureMode,
    CircleMode,
    ArrowMode,
    TextMode,
    MatrixMode,
    DeleteMode
};

enum ColAndRow {    
    Row,
    Col
};
const GLuint WIDTH = 1920, HEIGHT = 1080;

extern int maxFPS;
extern std::stack<Action> ActionStack;
extern Mode mode;
extern bool ctrlPressed;
extern float* controledSize;
extern float* controledRows;
extern float* controledColums;
extern glm::vec2* controledPos;
extern glm::vec2* controledDir;
extern float DeleteButtonSize;


#endif 