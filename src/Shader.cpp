#include "Shader.h"

void Shader::setUniformM4f(const std::string& name, glm::mat4& matrix)
{
    int location = getUniformLocation(name);
    if (location == -1)
    {
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformVec3f(const std::string& name, glm::vec3 vec)
{
    int location = getUniformLocation(name);
    if (location == -1)
    {
        return;
    }
    glUniform3fv(location, 1, &vec[0]);
}

void Shader::setUniformVec3f(const std::string& name, float data[3])
{
    int location = getUniformLocation(name);
    if (location == -1)
    {
        return;
    }
    glUniform3fv(location, 1, data);
}

void Shader::setUniform1f(const std::string& name, float f)
{
    int location = getUniformLocation(name);
    if (location == -1)
    {
        return;
    }
    glUniform1f(location, f);
}

void Shader::setUniformMaterial(const std::string& name, Material& mat)
{
    setUniform1f(name + ".ns", mat.ns);
    setUniformVec3f(name + ".ka", mat.ka);
    setUniformVec3f(name + ".ks", mat.ks);
    setUniformVec3f(name + ".kd", mat.kd);
    setUniformVec3f(name + ".ke", mat.ke);
    setUniform1f(name + ".ni", mat.ni);
    setUniform1f(name + ".d", mat.d);
    setUniform1f(name + ".illum", mat.illum);
}

int Shader::getUniformLocation(const std::string& name)
{
    if (cachedUniforms.find(name) != cachedUniforms.end())
        return cachedUniforms[name];
    int location = glGetUniformLocation(programID, name.c_str());
    cachedUniforms[name] = location;
    return location;
}

unsigned int Shader::compileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = new char[len];
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        delete[] message;
        return 0;
    }

    return id;
}

Shader::~Shader()
{
    //glDeleteShader(vertexID);
    //glDeleteShader(fragmentID);
    //glDeleteProgram(programID);
}

void Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    programID = glCreateProgram();

    vertexID = compileShader(vertexShader, GL_VERTEX_SHADER);
    fragmentID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);
    glValidateProgram(programID);
}

void Shader::loadShader(const std::string& filename_v, const std::string& filename_f)
{
    std::ifstream vertex("shader/" + filename_v + ".shader");
    std::ifstream fragment("shader/" + filename_f + ".shader");
    if (!vertex.is_open())
    {
        std::cout << "Couldnt load " << filename_v << std::endl;
        return;
    }
    if (!fragment.is_open())
    {
        std::cout << "Couldnt load " << filename_f << std::endl;
        return;
    }

    std::stringstream vex;
    std::stringstream frag;
    std::string line;
    while (getline(vertex, line))
    {
        vex << line << '\n';
    }
    while (getline(fragment, line))
    {
        frag << line << '\n';
    }
    createShader(vex.str(), frag.str());
}

void Shader::bind()
{
    glUseProgram(programID);
}
