#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global.h"
#include "imgui/imgui.h"
#include "vendor/glm/glm.hpp"


const int FLOATS_NUM = 2;
const int MAX_LINESS = 1000;
const int MAX_POINTS_IN_LINE = 100000;



extern bool ctrlPressed;
extern float* controledSize;
extern glm::vec2* controledPos;
extern bool moving ;
extern ImVec4 pen_color ;
extern float pen_width ;

//extern VertexArry VA[MAX_LINESS];
//extern VertexBuffer VB[MAX_LINESS];
extern int CURR_NUM_LINES;
extern int CURR_NUM_LINES_BUFFERED;
extern int NUM_POINTS_ARRAY[MAX_LINESS] ;
extern ImVec4 LINE_COLOR_ARRAY[MAX_LINESS] ;
extern float LINE_WIDTH_ARRAY[MAX_LINESS];
extern GLfloat pointesArry[MAX_LINESS][MAX_POINTS_IN_LINE];


extern void PenReset();
extern void PenUndo();
extern void addPoint(float xpos, float ypos);
extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);