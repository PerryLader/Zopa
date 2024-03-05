#pragma once
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "vendor/glm/glm.hpp"
#include <vector>
#include <string>
#include "imgui/imgui.h"
#include "text.h"
#include "Shader.h"

extern ImVec4 text_color;
extern ImVec4 shape_color;
extern ColAndRow currMatrixMode;

class Shape
{
public:
	Shape() = default;
	Shape(glm::vec2 pos, float size, ImVec4 color)
		:m_pos(pos), m_size(size), m_color(color) {}
	~Shape() {}

	float* getSize() { return &m_size; }
	void setSize(float size) { this->m_size = size; }

	glm::vec2* getPos() { return &m_pos; }
	void setPos(glm::vec2 pos) { this->m_pos = pos; }

	ImVec4 getColor() { return m_color; }

	virtual float* getCol() { return nullptr; }
	virtual float* getRow(){ return nullptr; }

	virtual glm::vec2* getDir(){ return nullptr; }
	virtual void setDir(glm::vec2 dir) {}

	virtual ShapeType getType() { return ShapeType::TypeShape; }

	virtual void PushDeletedActionType() {}
	virtual void DrawShape (Shader* shader, float posX, float posY, float size, ImVec4 color ) {}

private:
	glm::vec2 m_pos;
	float m_size;
	ImVec4 m_color;
};

class SqureUnit :public Shape
{
public:
	SqureUnit() = default;
	SqureUnit(glm::vec2 pos, float size, ImVec4 color):Shape(pos,size,color) {}
	~SqureUnit() {}

	ShapeType getType() override { return ShapeType::TypeSqure; }

	void PushDeletedActionType() override { ActionStack.push(Action::DeletedSqure); }

	void DrawShape(Shader* shader, float posX, float posY, float size, ImVec4 color) override
	{
		float sizeX = size;
		float sizeY = size * WIDTH / HEIGHT;
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
		shader->SetUniform4f("f_shapecolor", color.x, color.y, color.z, color.w);
		tempVA.Bind();
		tempVB.Bind();
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		tempVA.UnBind();
		tempVB.UnBind();
	}

private:
	
};
class CircleUnit :public Shape
{
public:
	CircleUnit() = default;
	CircleUnit(glm::vec2 pos, float size, ImVec4 color) :Shape(pos, size, color){}
	~CircleUnit() {}
	
	ShapeType getType() override { return ShapeType::TypeCircle; }
	void PushDeletedActionType() override { ActionStack.push(Action::DeletedCircle); }
	void DrawShape(Shader* shader, float posX, float posY, float size, ImVec4 color) override
	{
		float sizeX = size;
		float sizeY = size * WIDTH / HEIGHT;
		float posC[130] = { 0 };
		for (int j = 0; j < 130; j += 2) {
			float angle = static_cast<float>(j) * 2.0f * (glm::pi<float>()) / 64;
			float x = posX + (sizeX * std::cos(angle));
			float y = posY + (sizeY * std::sin(angle));
			posC[j] = x;
			posC[j + 1] = y;
		}

		VertexArry tempVA;
		VertexBuffer tempVB(posC, 130 * sizeof(float));
		VertexBufferLayout tempVBL;
		tempVBL.Push<float>(2);
		tempVA.AddBuffer(tempVB, tempVBL);
		shader->SetUniform4f("f_shapecolor", color.x, color.y, color.z, color.w);

		tempVA.Bind();
		tempVB.Bind();
		glDrawArrays(GL_LINE_LOOP, 0, 64);
		tempVA.UnBind();
		tempVB.UnBind();
	}
private:


};
class ArrowUnit :public Shape
{
public:
	ArrowUnit() = default;
	ArrowUnit(glm::vec2 pos, glm::vec2 dir, float size, ImVec4 color):
		Shape(pos,size,color), m_dir(dir){}
	~ArrowUnit() {}

	glm::vec2* getDir() override { return &m_dir; }
	void setDir(glm::vec2 dir) override { this->m_dir = dir; }

	ShapeType getType() override { return ShapeType::TypeArrow; }
	void PushDeletedActionType() override { ActionStack.push(Action::DeletedArrow); }

	void DrawShape(Shader* shader, float posX, float posY, float size, ImVec4 color) override
	{
		glm::vec2 dir = *this->getDir();
		glm::vec2 posS = { posX,posY };
		glm::vec2 posE = posS + size * dir;

		glm::vec2 vertical = glm::vec2(-dir.y, dir.x); // This gives a vertical vector

		glm::vec2 ArrowverDiff = ((size + 0.4325f) * vertical * 0.025f);
		glm::vec2 ArrowdirDiff = ((size + 0.4325f) * dir * 0.025f);

		glm::vec2 ShaftverDiff = ((size + 0.01325f) * vertical * 0.0125f);
		glm::vec2 shaftFirst = posS + ShaftverDiff;
		glm::vec2 shaftSeconde = posS - ShaftverDiff;
		glm::vec2 shaftThird = posE + ShaftverDiff - ArrowdirDiff;
		glm::vec2 shaftFourth = posE - ShaftverDiff - ArrowdirDiff;

		glm::vec2 ArrowHeadL = posE - ArrowdirDiff - ArrowverDiff;
		glm::vec2 ArrowHeadR = posE - ArrowdirDiff + ArrowverDiff;


		GLfloat arrowVertices[] = {
			// Arrow shaft (line)
			shaftFirst.x, shaftFirst.y,
			shaftSeconde.x, shaftSeconde.y,
			shaftThird.x, shaftThird.y,
			shaftFourth.x, shaftFourth.y,

			// Arrowhead (triangle)
			posE.x, posE.y,
			ArrowHeadL.x, ArrowHeadL.y,
			ArrowHeadR.x, ArrowHeadR.y,
		};
		VertexArry tempVA;
		VertexBuffer tempVB(arrowVertices, sizeof(arrowVertices));
		VertexBufferLayout tempVBL;
		tempVBL.Push<float>(2);
		tempVA.AddBuffer(tempVB, tempVBL);
		shader->SetUniform4f("f_shapecolor", color.x, color.y, color.z, color.w);

		tempVA.Bind();
		tempVB.Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);     // Draw the shaft
		glDrawArrays(GL_TRIANGLES, 4, 3); // Draw the arrowhead
		tempVA.UnBind();
		tempVB.UnBind();
	}
private:
	
	glm::vec2 m_dir;
};
class MatrixUnit :public Shape
{
public:
	MatrixUnit() = default;
	MatrixUnit(glm::vec2 pos, float colums, float rows, float size, ImVec4 color)
		:Shape(pos, size, color),
		m_Colums(colums), m_Rows(rows) {}
	~MatrixUnit() {}

	
	float* getCol() override { return &m_Colums; }
	float* getRow() override { return &m_Rows; }

	ShapeType getType() override { return ShapeType::TypeMatrix; }
	void PushDeletedActionType() override { ActionStack.push(Action::DeletedMatrix); }
	void DrawShape(Shader* shader, float posX, float posY, float size, ImVec4 color) override
	{
		
		glm::vec2 TopLeft = glm::vec2(posX,posY) + glm::vec2(-size / 2, -size / 2);

		float rows=*this->getRow();
		float cols= *this->getCol();
		float rowspace = size / rows;
		float colspace = size / cols;

		GLfloat matrixVertices[64];
		//horizontal
		for (int i = 0; i < rows - 1; i++)
		{
			matrixVertices[(4 * i) + 0] = TopLeft.x;
			matrixVertices[(4 * i) + 1] = TopLeft.y + rowspace * (i + 1);
			matrixVertices[(4 * i) + 2] = TopLeft.x + size;
			matrixVertices[(4 * i) + 3] = TopLeft.y + rowspace * (i + 1);
		}
		int diff = (4 * (rows - 1));
		for (int i = 0; i < cols - 1; i++)
		{
			matrixVertices[diff + (4 * i) + 0] = TopLeft.x + colspace * (i + 1);
			matrixVertices[diff + (4 * i) + 1] = TopLeft.y;
			matrixVertices[diff + (4 * i) + 2] = TopLeft.x + colspace * (i + 1);
			matrixVertices[diff + (4 * i) + 3] = TopLeft.y + size;
		}


		VertexArry tempVA;
		VertexBuffer tempVB(matrixVertices, sizeof(matrixVertices));
		VertexBufferLayout tempVBL;
		tempVBL.Push<float>(2);
		tempVA.AddBuffer(tempVB, tempVBL);
		shader->SetUniform4f("f_shapecolor", color.x, color.y, color.z, color.w);

		tempVA.Bind();
		tempVB.Bind();
		glDrawArrays(GL_LINES, 0, (rows + cols - 2) * 2);     // Draw the shaft

		tempVA.UnBind();
		tempVB.UnBind();
	}
private:
	
	float m_Colums;
	float m_Rows;
	

};

class ShapesObj
{
public:
	ShapesObj() :m_DeletedShape(nullptr)  {}
	~ShapesObj(){}
	void Reset() {
		m_shapes.clear();
		m_text.clear();
		num_render_strings = 0;
	}
	void DeleteLastShape()
	{
		int size = m_shapes.size();
		delete m_shapes[size - 1];
		m_shapes.pop_back();
	}
	void AddSqure(SqureUnit s)
	{
		m_shapes.push_back(new SqureUnit(s));
		int size = m_shapes.size();
		controledSize = m_shapes[size - 1]->getSize();
		controledPos = m_shapes[size - 1]->getPos();
		ActionStack.push(Action::AddedSqure);
	}
	void AddCircle(CircleUnit c)
	{
		m_shapes.push_back(new CircleUnit(c));
		controledPos = m_shapes[(int)m_shapes.size() - 1]->getPos();
		controledSize = m_shapes[(int)m_shapes.size() - 1]->getSize();
		ActionStack.push(Action::AddedCircle);
	}
	void AddMatrix(MatrixUnit c)
	{
		m_shapes.push_back(new MatrixUnit(c));
		int size = m_shapes.size();
		controledSize = m_shapes[size - 1]->getSize();
		controledPos = m_shapes[size - 1]->getPos();
		controledColums = m_shapes[size - 1]->getCol();
		controledRows = m_shapes[size - 1]->getRow();
		ActionStack.push(Action::AddedMatrix);
	}
	void AddArrow(ArrowUnit c)
	{
		m_shapes.push_back(new ArrowUnit(c));
		int size = m_shapes.size();
		controledSize = m_shapes[size - 1]->getSize();
		controledPos = m_shapes[size - 1]->getPos();
		controledDir = m_shapes[size - 1]->getDir();
		ActionStack.push(Action::AddedArrow);
	}


	void RedoText(GLFWwindow* window)
	{
		std::pair<int, std::string> lastPair = m_text[(int)m_text.size() - 1];
		int nextId = Redo_Text(lastPair.first, lastPair.second.c_str(),window);
		m_text.push_back(std::pair<int, std::string>(nextId, lastPair.second.c_str()));
		ActionStack.push(Action::AddedText);
	}
	std::vector<Shape*> m_shapes;
	std::vector<std::pair<int,std::string>> m_text;
	Shape* m_DeletedShape;
	std::pair<Renderable_Text, std::string> m_DeletedText;
};


extern ShapesObj Allshapes;