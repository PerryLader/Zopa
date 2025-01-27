#pragma once
#include "global.h"
#include <string>
#include "vendor/stb/stb_image.h"


class Texture
{
public:
	Texture(const std::string &path);
	~Texture();
	void Bind(unsigned int slot=0) const;
	void UnBind() const;
	inline int GetWidth()const { return m_Width; }
	inline int GetHeight()const { return m_Height; }
private:
	unsigned int m_RenderID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, _m_BPP;
};
