#pragma once
#ifndef KEYBOARDINPUT  
#define KEYBOARDINPUT

#include "global.h"
#include "Shapes.h"
#include "Pen.h"
#include <GLFW/glfw3.h>
#include "text.h"
#include <string>

extern void KeyCalBack(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void KeyCharCalBack(GLFWwindow* window, unsigned int keyCode, int modifireKey);
extern void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
#endif 