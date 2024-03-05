#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global.h"
#include "imgui/imgui.h"
#include "vendor/glm/glm.hpp"
#include "Shapes.h"
#include "text.h"


const int FLOATS_NUM = 2;
const int MAX_LINESS = 1000;
const int MAX_POINTS_IN_LINE = 100000;




extern ImVec4 pen_color ;
extern float pen_width ;
extern int CURR_NUM_LINES_BUFFERED ;
extern std::vector<ImVec4> LINE_COLOR_ARRAY;
extern std::vector<float> LINE_WIDTH_ARRAY;
extern std::vector<std::vector<GLfloat>> pointesArry;

extern std::vector<GLfloat> lastDeletedPen;
extern ImVec4 lastDeletedPenColor;
extern float lastDeletedPenWidth;


extern void PenReset();
extern void PenUndo();
extern void addPoint(float xpos, float ypos);
extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);