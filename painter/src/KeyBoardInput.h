#pragma once
#include "global.h"
#include "Shapes.h"
#include "Pen.h"

extern bool ctrlPressed ;
extern float *controledSize;
extern glm::vec2* controledPos;

extern void KeyCalBack(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
