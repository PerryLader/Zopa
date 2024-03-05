#pragma once
#ifndef RENDERER  
#define RENDERER

#include <iostream>
#include <GL/glew.h>
#include "VertexArray.h"
#include "Shader.h"
#include "Pen.h"
#include "VertexBufferLayout.h"
#include "Shapes.h"
#include "Texture.h"


class Renderer
{
public:
	void DrawPen(VertexArry* VA,  Shader* shader, VertexBuffer* VB) ;
	void DrawShapes(Shader* shader);
	void DrawDeleteButtons(Shader* shader,Texture* tex);

	void Clear() const;
	void SetBackGroundColor(float v0, float v1, float v2, float v3);

};
#endif 
