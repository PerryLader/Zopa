#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "vendor/glm/glm.hpp"

struct  ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometryShader;

};

class Shader 
{
public:

	Shader (const std::string& filepath ,bool withGeo);
	void Bind() const;
	void UnBind() const;
	~Shader ();
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform1i(const std::string& name, int v0);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	unsigned int m_RendererID;
private:
	bool m_withGeo;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	int GetUniformLocation(const std::string& name);
	unsigned int createShaders(const std::string& vertexShader, const std::string& geometryShader, const std::string& freagShader);
	unsigned int compileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filePath);
};
