


#include "Renderer.h"
#include "vendor/glm/glm.hpp"

#include "vendor/glm/gtc/matrix_transform.hpp"


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
		glDrawArrays(GL_LINE_STRIP, 0, NUM_POINTS_ARRAY[i] - 1);
		VA[i].UnBind();
	}
	for (int i = CURR_NUM_LINES_BUFFERED; i <= CURR_NUM_LINES; i++) {
		if (NUM_POINTS_ARRAY[CURR_NUM_LINES] > 0 && NUM_POINTS_ARRAY[CURR_NUM_LINES] < MAX_POINTS_IN_LINE / FLOATS_NUM)
		{
			VertexBuffer tempVB(&pointesArry[i][0], sizeof(GLfloat) * FLOATS_NUM * NUM_POINTS_ARRAY[i]);
			VB[i] = tempVB;
			VA[i].Bind();
			VB[i].Bind();
			VertexBufferLayout layout;
			layout.Push<float>(2);
			//layout.Push<float>(4);
			VA[i].AddBuffer(VB[i], layout);
			VB[i].UnBind();
			VA[i].UnBind();
		}
		shader->SetUniform1f("lineWidth", (0.00533 * (LINE_WIDTH_ARRAY[i] - 1)) - 0.002);
		shader->SetUniform4f("f_Pencolor", LINE_COLOR_ARRAY[i].x, LINE_COLOR_ARRAY[i].y, LINE_COLOR_ARRAY[i].z, LINE_COLOR_ARRAY[i].z);

		VA[i].Bind();
		glDrawArrays(GL_LINE_STRIP, 0, NUM_POINTS_ARRAY[i] - 1);
		VA[i].UnBind();
	}
	CURR_NUM_LINES_BUFFERED = CURR_NUM_LINES;
	shader->UnBind();
}
void Renderer::DrawShapes( Shader* shader)
{
	//glUseProgram(0);
	shader->Bind();
	for (int i = 0; i < Allshapes.m_squres.m_squresCount; i++)
	{
		SqureUnit s = Allshapes.m_squres.m_SquresArray[i];
		float posX = (*s.getPos()).x;
		float posY = (*s.getPos()).y;
		float sizeX = *s.getSize() ;
		float sizeY = *s.getSize() * WIDTH / HEIGHT;


		float pos[] = {
			posX - sizeX,posY - sizeY,
			posX + sizeX,posY - sizeY,
			posX + sizeX,posY + sizeY,
			posX - sizeX,posY + sizeY
		};
		VertexArry tempVA;
		VertexBuffer tempVB(pos, 8 * sizeof(float));
		VertexBufferLayout tempVBL;
		tempVBL.Push<float>(2);
		tempVA.AddBuffer(tempVB, tempVBL);
		tempVA.Bind();
		tempVB.Bind();
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		tempVA.UnBind();
		tempVB.UnBind();
	}

	for (int i = 0; i < Allshapes.m_circles.m_circlesCount; i++)
	{
		CircleUnit s = Allshapes.m_circles.m_CirclesArray[i];
		float posX = (*s.getPos()).x;
		float posY = (*s.getPos()).y;
		float sizeX = *s.getSize();
		float sizeY = *s.getSize() * (WIDTH / HEIGHT);


		float posC[130] = {0};

		
		for (int j = 0; j < 130;j+=2) {
			float angle = static_cast<float>(j)  * 2.0f *( glm::pi<float>()) / 64;
			float x = posX + (sizeX * std::cos(angle));
			float y = posY + (sizeY*1.65 * std::sin(angle));
			posC[j] = x;
			posC[j + 1] = y;
		}



		VertexArry tempVA;
		VertexBuffer tempVB(posC, 130 * sizeof(float));
		VertexBufferLayout tempVBL;
		tempVBL.Push<float>(2);
		tempVA.AddBuffer(tempVB, tempVBL);
		tempVA.Bind();
		tempVB.Bind();
		glDrawArrays(GL_LINE_LOOP, 0, 64);
		tempVA.UnBind();
		tempVB.UnBind();
	}
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
