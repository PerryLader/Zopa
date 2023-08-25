#include "Pen.h"



bool moving = false;
ImVec4 pen_color = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
float pen_width = 2.0f;
int CURR_NUM_LINES = 0;
int CURR_NUM_LINES_BUFFERED = 0;
int NUM_POINTS_ARRAY[MAX_LINESS] = { 0 };
ImVec4 LINE_COLOR_ARRAY[MAX_LINESS] = { ImVec4(0.0f,0.0f,0.0f,1.0f) };
float LINE_WIDTH_ARRAY[MAX_LINESS] = { 1.0 };
GLfloat pointesArry[MAX_LINESS][MAX_POINTS_IN_LINE];



void PenReset()
{
	CURR_NUM_LINES = 0;
	CURR_NUM_LINES_BUFFERED = 0;
	for (int i = 0; i < MAX_LINESS; i++)
	{
		NUM_POINTS_ARRAY[i] = 0;
		LINE_COLOR_ARRAY[i] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		LINE_WIDTH_ARRAY[i] = 0;
	}
}
void PenUndo()
{
	if (CURR_NUM_LINES_BUFFERED != 0)
	{
		CURR_NUM_LINES_BUFFERED--;
	}
	if (CURR_NUM_LINES != 0)
	{
		CURR_NUM_LINES--;
	}
	NUM_POINTS_ARRAY[CURR_NUM_LINES] = 0;
	LINE_COLOR_ARRAY[CURR_NUM_LINES] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	LINE_WIDTH_ARRAY[CURR_NUM_LINES] = 0;

}
void addPoint(float xpos, float ypos) {
	if (NUM_POINTS_ARRAY[CURR_NUM_LINES] >= MAX_POINTS_IN_LINE / FLOATS_NUM)return;
	float dotX = 2 * (float)xpos / WIDTH - 1.0f;
	float dotY = 1 - 2 * (float)(ypos / HEIGHT);
	pointesArry[CURR_NUM_LINES][FLOATS_NUM * NUM_POINTS_ARRAY[CURR_NUM_LINES]] = dotX;
	pointesArry[CURR_NUM_LINES][FLOATS_NUM * NUM_POINTS_ARRAY[CURR_NUM_LINES] + 1] = dotY;

	NUM_POINTS_ARRAY[CURR_NUM_LINES]++;
	LINE_WIDTH_ARRAY[CURR_NUM_LINES] = pen_width;
	LINE_COLOR_ARRAY[CURR_NUM_LINES] = pen_color;



}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && controledPos && ctrlPressed)
	{
		printf("done");
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		float dotX = 2 * (float)xpos / WIDTH - 1.0f;
		float dotY = 1 - 2 * (float)(ypos / HEIGHT);
		*controledPos = glm::vec2(dotX, dotY);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS&& !controledPos && !ctrlPressed)
	{

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		addPoint(xpos, ypos);
		moving = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		moving = false;
		CURR_NUM_LINES++;
		ActionStack.push(Action::PenLine);
	}
}
