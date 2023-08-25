#include "KeyBoardInput.h"
 bool ctrlPressed = false;
 float* controledSize = nullptr;
 glm::vec2 * controledPos= nullptr;

 void KeyCalBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {
	 if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
	 {
		 ctrlPressed = false;
		 controledSize = nullptr;
		 controledPos = nullptr;
	 }

	 if (key == GLFW_KEY_Z && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
	 {

		 if (ActionStack.top() == PenLine)
		 {
			 ActionStack.pop();
			 PenUndo();
		 }
	 }

	 
	 if (key == GLFW_KEY_S && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
	 {
		 ctrlPressed = true;
		 glm::vec2 pos(0.0f, 0.0f);
		 Allshapes.m_squres.AddSqure(SqureUnit(pos, 0.1f));
		 controledSize = Allshapes.m_squres.m_SquresArray.back().getSize();
		 controledPos = Allshapes.m_squres.m_SquresArray.back().getPos();

	 }
	 if (key == GLFW_KEY_C && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
	 {
		 ctrlPressed = true;
		 glm::vec2 pos(0.0f, 0.0f);
		 Allshapes.m_circles.AddCircle(CircleUnit(pos, 0.1f));
		 controledSize = Allshapes.m_circles.m_CirclesArray.back().getSize();
		 controledPos = Allshapes.m_circles.m_CirclesArray.back().getPos();
	 }

 }
 void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
 {
	 if (ctrlPressed)
	 {
		 if (controledSize)
		 {
			 if (yoffset > 0)
			 {
				 *controledSize = *controledSize + 0.05;

			 }
			 else
			 {

				 *controledSize = *controledSize - 0.05;
				 if (*controledSize < 0)
				 {
					 *controledSize = 0;
				 }

			 }
		 }
	 }

 }