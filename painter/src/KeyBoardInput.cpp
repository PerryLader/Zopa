#include "KeyBoardInput.h"

ColAndRow currMatrixMode = ColAndRow::Row;
void KeyCalBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//ctrl pressed
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{
		ctrlPressed = true;
	}
	//ctrl released
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
	{
		// printf("control release \n");
		if (mode == Mode::CircleMode || mode == Mode::SqureMode)
		{
			mode = Mode::Idle;
		}
		ctrlPressed = false;
	}
	// backspace is pressed in text
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS &&
		(mode == Mode::TextMode || mode == Mode::MatrixMode))
	{
		KeyCharCalBack(window, -1, 0);
	}
	// enter is pressed in text
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS &&
		(mode == Mode::TextMode || mode == Mode::MatrixMode))
	{
		KeyCharCalBack(window, -2, 0);
	}
	//ctrl z
	if (key == GLFW_KEY_Z && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS && mode == Mode::Idle)
	{
		if (!ActionStack.empty())
		{
			int tempId;
			Action LastAction = ActionStack.top();
			if (LastAction == AddedPenLine)
			{
				PenUndo();
			}
			else if (LastAction == AddedCircle|| LastAction == AddedSqure || LastAction == AddedArrow || LastAction == AddedMatrix )
			{
				Allshapes.DeleteLastShape();
			}			
			else if (LastAction == AddedText)
			{
				if (!Allshapes.m_text.empty())
				{
					num_render_strings--;
					Allshapes.m_text.pop_back();
				}
			}
			else if (LastAction == Action::DeletedPen||LastAction == Action::DeletedSqure|| LastAction == Action::DeletedCircle || LastAction == Action::DeletedArrow || LastAction == Action::DeletedMatrix|| LastAction == Action::DeletedText)
			{
				ActionStack.pop();
				Shape* LastShape=Allshapes.m_DeletedShape;
				switch (LastAction)
				{
				case Action::DeletedArrow:
					Allshapes.AddArrow(ArrowUnit(*LastShape->getPos(), *LastShape->getDir(), *LastShape->getSize(), LastShape->getColor()));
					break;

				case Action::DeletedMatrix:
					Allshapes.AddMatrix(MatrixUnit(*LastShape->getPos(), *LastShape->getCol(), *LastShape->getRow(), *LastShape->getSize(), LastShape->getColor()));
					break;

				case Action::DeletedCircle:
					Allshapes.AddCircle(CircleUnit(*LastShape->getPos(), *LastShape->getSize(), LastShape->getColor()));
					break;

				case Action::DeletedSqure:
					Allshapes.AddSqure(SqureUnit(*LastShape->getPos(), *LastShape->getSize(), LastShape->getColor()));
					break;

				case Action::DeletedText:
					 tempId = add_text(
						Allshapes.m_DeletedText.second.c_str(),
						Allshapes.m_DeletedText.first.tl_x, Allshapes.m_DeletedText.first.tl_y, 35.0f, text_color.x, text_color.y, text_color.z, text_color.w);
					Allshapes.m_text.push_back(std::pair<int, std::string>(tempId, Allshapes.m_DeletedText.second.c_str()));
					ActionStack.push(Action::AddedText);
					break;	
				case Action::DeletedPen:
					pointesArry.push_back(lastDeletedPen);
					LINE_COLOR_ARRAY.push_back(lastDeletedPenColor);
					LINE_WIDTH_ARRAY.push_back(lastDeletedPenWidth);
					ActionStack.push(Action::AddedPenLine);

				}
				mode = Idle;
				Allshapes.m_DeletedShape = nullptr;
				Allshapes.m_DeletedText = std::pair<Renderable_Text, std::string>();
				
			}
			ActionStack.pop();
		}
		mode = Mode::Idle;
	}
	// create squre
	if (key == GLFW_KEY_S && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS && mode == Mode::Idle)
	{
		//printf("new squre\n");

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		float dotX = 2 * (float)xpos / WIDTH - 1.0f;
		float dotY = 1 - 2 * (float)(ypos / HEIGHT);
		glm::vec2 pos(dotX, dotY);
		Allshapes.AddSqure(SqureUnit(pos, 0.1f, shape_color));
		mode = Mode::SqureMode;
	}
	//create circle
	if (key == GLFW_KEY_C && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS && mode == Mode::Idle)
	{
		//printf("new circle\n");
		mode = Mode::CircleMode;

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		float dotX = 2 * (float)xpos / WIDTH - 1.0f;
		float dotY = 1 - 2 * (float)(ypos / HEIGHT);
		glm::vec2 pos(dotX, dotY);
		Allshapes.AddCircle(CircleUnit(pos, 0.1f, shape_color));
		mode = Mode::CircleMode;

	}
	//create or finish edit of arrow
	if (key == GLFW_KEY_A && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS &&
		(mode == Mode::Idle || mode == Mode::ArrowMode))
	{
		if (mode == Mode::ArrowMode)
		{
			mode = Mode::Idle;
		}
		else
		{
			mode = Mode::ArrowMode;
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			float dotX = 2 * (float)xpos / WIDTH - 1.0f;
			float dotY = 1 - 2 * (float)(ypos / HEIGHT);
			glm::vec2 posS(dotX, dotY);
			Allshapes.AddArrow(ArrowUnit(posS, { 1.0f,0.0f }, 0.5f, shape_color));
		}
	}
	//create or finish edit of text
	if (key == GLFW_KEY_T && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS &&
		(mode == Mode::Idle || mode == Mode::TextMode))
	{
		// printf("new circle\n");
		if (mode == Mode::TextMode)
		{
			mode = Mode::Idle;
		}
		else
		{
			mode = Mode::TextMode;

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			float dotX = 2 * (float)xpos / WIDTH - 1.0f;
			float dotY = 1 - 2 * (float)(ypos / HEIGHT);
			int tempId = add_text(
				"text here :)",
				dotX, dotY, 35.0f, text_color.x, text_color.y, text_color.z, text_color.w);
			Allshapes.m_text.push_back(std::pair<int, std::string>(tempId, "text here :)"));
			ActionStack.push(Action::AddedText);

		}
	}
	//create or finish edit of matrix
	if (key == GLFW_KEY_M && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS &&
		(mode == Mode::Idle || mode == Mode::MatrixMode))
	{
		if (mode == Mode::MatrixMode)
		{
			mode = Mode::Idle;
		}
		else
		{
			mode = Mode::MatrixMode;
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			float dotX = 2 * (float)xpos / WIDTH - 1.0f;
			float dotY = 1 - 2 * (float)(ypos / HEIGHT);
			glm::vec2 pos(dotX, dotY);
			Allshapes.AddMatrix(MatrixUnit(pos, 2, 2, 0.5f, shape_color));			
		}
	}
	if (key == GLFW_KEY_D && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS &&
		(mode == Mode::DeleteMode ||mode == Mode::Idle))
	 {
		if (mode == Mode::DeleteMode)
		{
			mode = Mode::Idle;
		}
		else
		{
			mode = Mode::DeleteMode;
		}
	 }
	
 }
 void KeyCharCalBack(GLFWwindow* window, unsigned int keyCode, int modifireKey)
 {
	// printf("keyCode:%d\n", keyCode);
	 if (mode==Mode::TextMode)
	 {
		
		 int size = Allshapes.m_text.size();
		 if (Allshapes.m_text[size - 1].second == "text here :)")
		 {
			 if (keyCode == -2)
			 {
				 Allshapes.m_text[size - 1].second = (char)10;
			 }
			 else
			 {
				 Allshapes.m_text[size - 1].second = (char)keyCode;

			 }
		 }
		 else
		 {

			 if (keyCode == -2)
			 {
				 Allshapes.m_text[size - 1].second += (char)10;
			 }
			 else if (keyCode == -1)
			 {
				 if (!Allshapes.m_text[size - 1].second.empty())
				 {
					 Allshapes.m_text[size - 1].second.pop_back();
				 }
			 }
			 else 
			 {
				 Allshapes.m_text[size - 1].second += (char)keyCode;

			 }

		 }
		 std::pair<int,std::string> tempPair= Allshapes.m_text[size - 1];
		 update_text(tempPair.first, tempPair.second.c_str()); 
	 }
	 else if(mode == Mode::MatrixMode)
	 {
		 

		 if (currMatrixMode == ColAndRow::Row)
		 {
			 if (keyCode == -2)
			 {

				 currMatrixMode = ColAndRow::Col;
			 }
			 else if (keyCode >= 50&&keyCode<=57)
			 {
				
				 *controledRows = (float)keyCode - 48;
			 }			 
		 }
		 else
		 {
			 if (keyCode == -1)
			 {
				 currMatrixMode = ColAndRow::Row;
			 }
			 else if (keyCode >= 50 && keyCode <= 57)
			 {
				 *controledColums = (float)keyCode - 48;
			 }
		 }




		 
	 }
	
 }
 void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
 {
	 if (mode !=Mode::Idle)
	 {
		 if (mode == Mode::ArrowMode|| mode == Mode::CircleMode || mode == Mode::SqureMode|| mode == Mode::MatrixMode)
		 {			
			 if (yoffset > 0)
			 {
				 *controledSize = *controledSize + 0.0125;
			 }
			 else
			 {
				 *controledSize = *controledSize - 0.0125;
				 if (*controledSize < 0)
				 {
					 *controledSize = 0;
				 }
			 }
		 }
		 if (mode == Mode::TextMode)
		 {
			 int size = Allshapes.m_text.size();
			 int updatedId = Allshapes.m_text[size - 1].first;
			 std::string tempString = Allshapes.m_text[size - 1].second;
			 if (yoffset > 0)
			 {				
				 changeSize_text(updatedId, 2.0f, tempString.c_str());

			 }
			 else
			 {
				 changeSize_text(updatedId, -2.0f, tempString.c_str());
			 }
		 }
	 }
 }