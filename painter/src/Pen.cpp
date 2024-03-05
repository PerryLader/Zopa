#include "Pen.h"




ImVec4 pen_color = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
float pen_width = 2.0f;

int CURR_NUM_LINES_BUFFERED = 0;
std::vector<ImVec4> LINE_COLOR_ARRAY;
std::vector<float> LINE_WIDTH_ARRAY;
std::vector<std::vector<GLfloat>> pointesArry;

std::vector<GLfloat> lastDeletedPen;
ImVec4 lastDeletedPenColor;
float lastDeletedPenWidth;

bool Cliked(glm::vec2 clickPos, glm::vec2 shapePos)
{
	float sizeX = DeleteButtonSize;
	float sizeY = sizeX * WIDTH / HEIGHT;;
	if (clickPos.x <= shapePos.x + sizeX && clickPos.x >= shapePos.x - sizeX &&
		clickPos.y <= shapePos.y + sizeY && clickPos.y >= shapePos.y - sizeY)
	{
		return true;
	}
	return false;
}
void PenReset()
{

	CURR_NUM_LINES_BUFFERED = 0;


	LINE_COLOR_ARRAY.clear();
	LINE_WIDTH_ARRAY.clear();
	pointesArry.clear();

}
void PenUndo()
{
	if (CURR_NUM_LINES_BUFFERED != 0)
	{
		CURR_NUM_LINES_BUFFERED--;
	}
	
	
	LINE_COLOR_ARRAY.pop_back();
	LINE_WIDTH_ARRAY.pop_back();
	pointesArry.pop_back();

}
void addPoint(float xpos, float ypos) {	
	float dotX = 2 * (float)xpos / WIDTH - 1.0f;
	float dotY = 1 - 2 * (float)(ypos / HEIGHT);
	pointesArry[(int)pointesArry.size() - 1].push_back(dotX);
	pointesArry[(int)pointesArry.size() - 1].push_back(dotY);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{	//delete shapes
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mode == Mode::DeleteMode)
	{		
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		float clickX = 2 * (float)xpos / WIDTH - 1.0f;
		float clickY = 1 - 2 * (float)(ypos / HEIGHT);
		//squre
		int size = Allshapes.m_shapes.size();
		for (int i = 0; i < size; i++)
		{
			Shape *s = Allshapes.m_shapes[i];
			float posX = (*s->getPos()).x;
			float posY = (*s->getPos()).y;
			if (Cliked({ clickX,clickY }, { posX,posY }))
			{
				size--;
				while (!ActionStack.empty())
				{
					ActionStack.pop();
				}

				s->PushDeletedActionType();
				
				Allshapes.m_DeletedShape= Allshapes.m_shapes[i];
				Allshapes.m_shapes.erase(Allshapes.m_shapes.begin() + i);	
			}
		}
		
		//text		
		size = Allshapes.m_text.size();
		for (int i = 0; i < size; i++)
		{
			glm::vec2 pos = TextgetPos(Allshapes.m_text[i].first);
			float posX = pos.x;
			float posY = pos.y;
			if (Cliked({ clickX,clickY }, { posX,posY }))
			{
				size--;
				while (!ActionStack.empty())
				{
					ActionStack.pop();
				}
				ActionStack.push(Action::DeletedText);
				Allshapes.m_DeletedText = std::pair<Renderable_Text, std::string> ( renderable_texts[Allshapes.m_text[i].first], Allshapes.m_text[i].second);
				delete_text(Allshapes.m_text[i].first);
				Allshapes.m_text.erase(Allshapes.m_text.begin() + i);				
			}
		}
		//pen
		size = pointesArry.size();
		for (int i = 0; i < size; i++)
		{
			
			glm::vec2 pos = glm::vec2(pointesArry[i][0], pointesArry[i][1]);
			float posX = pos.x;
			float posY = pos.y;
			if (Cliked({ clickX,clickY }, { posX,posY }))
			{
				size--;
				while (!ActionStack.empty())
				{
					ActionStack.pop();
				}
				ActionStack.push(Action::DeletedPen);
				CURR_NUM_LINES_BUFFERED = 0;
				lastDeletedPen = pointesArry[i];
				lastDeletedPenColor = LINE_COLOR_ARRAY[i];
				lastDeletedPenWidth = LINE_WIDTH_ARRAY[i];
				pointesArry.erase(pointesArry.begin() + i);
				LINE_COLOR_ARRAY.erase(LINE_COLOR_ARRAY.begin() + i);
				LINE_WIDTH_ARRAY.erase(LINE_WIDTH_ARRAY.begin() + i);
			}
		}
		
		
		
		
		
		
		if ((int)Allshapes.m_text.size() == 0 && (int)Allshapes.m_shapes.size() == 0)
			mode == Mode::Idle;
	
	}
	//moving shapes and text
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		int size = Allshapes.m_text.size();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		float dotX = 2 * (float)xpos / WIDTH - 1.0f;
		float dotY = 1 - 2 * (float)(ypos / HEIGHT);
		switch (mode)
		{
		case Idle:
			break;
		case PenMode:
			break;
		case SqureMode:
			*controledPos = glm::vec2(dotX, dotY);
			break;
		case CircleMode:
			*controledPos = glm::vec2(dotX, dotY);
			break;
		case ArrowMode:
			if (ctrlPressed)
			{
				*controledPos = glm::vec2(dotX, dotY);
			}
			else if (controledDir && controledPos && controledSize && mode == Mode::ArrowMode)
			{
				*controledDir = glm::normalize(glm::vec2(dotX, dotY) - *controledPos);
				*controledSize = glm::length(glm::vec2(dotX, dotY) - (*controledPos));
			}
			break;
		case TextMode:
			move_text(Allshapes.m_text[size - 1].first, dotX, dotY);
			break;
		case MatrixMode:
			*controledPos = glm::vec2(dotX, dotY);
			break;
		default:
			break;
		}





	}
	//start draw
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mode == Mode::Idle)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		pointesArry.push_back(std::vector<GLfloat>());
		LINE_COLOR_ARRAY.push_back(pen_color);
		LINE_WIDTH_ARRAY.push_back(pen_width);
		addPoint(xpos, ypos);
		mode = Mode::PenMode;	
	}
	//end draw
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && mode == Mode::PenMode) {		
		mode = Mode::Idle;		
		ActionStack.push(Action::AddedPenLine);
	}
	
}
