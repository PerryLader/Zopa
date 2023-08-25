#pragma once
#include "VertexBuffer.h"
#include "global.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;
class VertexArry
{
public:
	unsigned int m_RendererID;
public :
	VertexArry();
	~VertexArry();
	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
