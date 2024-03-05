


#include "Renderer.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


std::vector<VertexBuffer> VB;
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
}
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << error << ": " << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}



void Renderer::DrawPen( VertexArry* VA, Shader *shader , VertexBuffer* VB) 
{
	shader->Bind();
	for (int i = 0; i < CURR_NUM_LINES_BUFFERED; i++) {
		shader->SetUniform4f("f_Pencolor", LINE_COLOR_ARRAY[i].x, LINE_COLOR_ARRAY[i].y, LINE_COLOR_ARRAY[i].z, LINE_COLOR_ARRAY[i].z);
		shader->SetUniform1f("lineWidth", (0.00533 * (LINE_WIDTH_ARRAY[i] - 1)) - 0.002);

		VA[i].Bind();
		glDrawArrays(GL_LINE_STRIP, 0, ((int)pointesArry[i].size() / 2) -2);
		VA[i].UnBind();
	}
	for (int i = CURR_NUM_LINES_BUFFERED; i < (int)pointesArry.size(); i++) {

		VertexBuffer tempVB(&pointesArry[i][0], sizeof(GLfloat)* ((int)pointesArry[i].size() - 1));
		VB[i] = tempVB;
		VA[i].Bind();
		VB[i].Bind();
		VertexBufferLayout layout;
		layout.Push<float>(2);
		//layout.Push<float>(4);
		VA[i].AddBuffer(VB[i], layout);
		VB[i].UnBind();
		VA[i].UnBind();

		shader->SetUniform1f("lineWidth", (0.00533 * (LINE_WIDTH_ARRAY[i] - 1)) - 0.002);
		shader->SetUniform4f("f_Pencolor", LINE_COLOR_ARRAY[i].x, LINE_COLOR_ARRAY[i].y, LINE_COLOR_ARRAY[i].z, LINE_COLOR_ARRAY[i].z);

		VA[i].Bind();
		glDrawArrays(GL_LINE_STRIP, 0, ((int)pointesArry[i].size()/2) - 2);
		VA[i].UnBind();
	}
	
	CURR_NUM_LINES_BUFFERED = (int)pointesArry.size()-1;
	if (CURR_NUM_LINES_BUFFERED == -1)
	{
		CURR_NUM_LINES_BUFFERED = 0;
	}
	shader->UnBind();
}
void Renderer::DrawShapes( Shader* shader)
{
	glUseProgram(0);
	shader->Bind();
	int Arraysize = Allshapes.m_shapes.size();
	for (int i = 0; i < Arraysize; i++)
	{
		Shape* s = Allshapes.m_shapes[i];
		glm::vec2 pos = (*s->getPos());
		float posX = pos.x;
		float posY = pos.y;
		float size = *s->getSize();
		ImVec4 color = s->getColor();
		

		s->DrawShape(shader, posX, posY, size, color);
	}
	shader->UnBind();	
}
void drawTexureHelper(float posX,float posY)
{
	float sizeX = DeleteButtonSize;
	float sizeY = sizeX * WIDTH / HEIGHT;

	float pos[] = {
		posX + sizeX,posY - sizeY, 1.0f,0.0f,   //buttom right
		posX - sizeX,posY - sizeY, 0.0f,0.0f,   //buttom left			
		posX + sizeX,posY + sizeY, 1.0f, 1.0f,  //top right
		posX - sizeX,posY + sizeY, 0.0f, 1.0f,  //top left
	};

	VertexArry tempVA;
	VertexBuffer tempVB(pos, 16 * sizeof(float));
	VertexBufferLayout tempVBL;
	tempVBL.Push<float>(2);
	tempVBL.Push<float>(2);

	tempVA.AddBuffer(tempVB, tempVBL);

	tempVA.Bind();
	tempVB.Bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	tempVA.UnBind();
	tempVB.UnBind();
}
void Renderer::DrawDeleteButtons(Shader* shader, Texture* tex)
{	
	shader->Bind();	
	tex->Bind(1);
	shader->SetUniform1i("u_Texture", 0);
	//shapes
	int size = Allshapes.m_shapes.size();
	for (int i = 0; i < size; i++)
	{		
		Shape *s = Allshapes.m_shapes[i];
		float posX = (*s->getPos()).x;
		float posY = (*s->getPos()).y;
		drawTexureHelper(posX, posY);
		
	}
	//text
	size = Allshapes.m_text.size();
	for (int i = 0; i < size; i++)
	{
		glm::vec2 pos = TextgetPos(Allshapes.m_text[i].first);	
		drawTexureHelper(pos.x, pos.y);
	}

	//pen
	size = pointesArry.size();
	for (int i = 0; i < size; i++)
	{
		glm::vec2 pos =glm::vec2(pointesArry[i][0], pointesArry[i][1]);
		drawTexureHelper(pos.x, pos.y);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	shader->UnBind();
}


void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SetBackGroundColor(float v0, float v1, float v2, float v3)
{
    glClearColor(v0,v1,v2,v3);

}
