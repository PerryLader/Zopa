#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global.h"


class VertexBuffer
{
public:
	VertexBuffer():m_RendererID(-1) {}
	VertexBuffer(const void* data,unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;

	unsigned int m_RendererID;
};

