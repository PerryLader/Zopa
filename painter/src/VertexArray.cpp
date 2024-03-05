#include "VertexArray.h"

VertexArry::VertexArry()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	
}

VertexArry::~VertexArry()
{
	GLCall(glDeleteVertexArrays(1,&m_RendererID))
}

void VertexArry::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));

}

void VertexArry::UnBind() const
{
	GLCall(glBindVertexArray(0));

}

void VertexArry::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (GLuint i = 0; i < elements.size(); i++)
	{
		const auto& element=elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
			layout.GetStride(),(const GLvoid*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

	}
	
	
}
