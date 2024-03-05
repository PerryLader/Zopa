#include "Shader.h"
#include "Renderer.h"





Shader::Shader(const std::string& filepath, bool withGeo):m_FilePath(filepath),m_withGeo(withGeo), m_RendererID(0)
{

    ShaderProgramSource source = ParseShader(filepath);
    
    
    m_RendererID = createShaders(source.vertexShader,source.geometryShader, source.fragmentShader);
}
Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}
void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}
void Shader::UnBind() const
{
    (glUseProgram(0));
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
void Shader::SetUniform1f(const std::string& name, float v0)
{
    GLCall(glUniform1f(GetUniformLocation(name), v0));

}
void Shader::SetUniform1i(const std::string& name, int v0)
{
    GLCall(glUniform1i(GetUniformLocation(name), v0));

}
int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "warning:uniform " << name.c_str() << std::endl;
    
    m_UniformLocationCache[name] = location;
    return location;
}
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
unsigned int Shader::createShaders(const std::string& vertexShader,const std::string& geometryShader,const std::string& freagShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, freagShader);
    unsigned int gs;
    if (m_withGeo)
    {
         gs = compileShader(GL_GEOMETRY_SHADER, geometryShader);
    }
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    if (m_withGeo)
    {
        GLCall(glAttachShader(program, gs));
    }

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    GLCall(glDeleteShader(fs));
    GLCall(glDeleteShader(vs));
    if (m_withGeo)
    {
        GLCall(glDeleteShader(gs));
    }
    return program;
}
unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* massage = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, massage));
        std::cout << "errorrrrrrrr" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment/OR geometry") << std::endl;
        std::cout << massage << std::endl;

        GLCall(glDeleteShader(id));
        return 0;

    }
    return id;
}
 ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1,GEOMETRY=2
    };



    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss[3];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {

        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else if (line.find("geometry") != std::string::npos)
                type = ShaderType::GEOMETRY;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }

    }
    return { ss[0].str(),ss[1].str(),ss[2].str() };
}