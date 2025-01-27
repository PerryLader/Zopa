#include "Texture.h"

Texture::Texture(const std::string& path):m_RenderID(0), m_FilePath(path)
,m_LocalBuffer(nullptr),m_Height(0),m_Width(0),_m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &_m_BPP, 4);
	
	
	GLCall(glGenTextures(1, &m_RenderID));
	//printf("m_RenderID:%d\n", m_RenderID);
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));	
	
	if (m_LocalBuffer)
	{		
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		stbi_image_free(m_LocalBuffer);
	}
	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
Texture::~Texture()
{
	GLCall(glDeleteTextures(1,&m_RenderID));

}
void Texture::Bind(unsigned int slot) const
{	
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}
void Texture::UnBind() const
{	
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
