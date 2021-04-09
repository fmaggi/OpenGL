#pragma once

#include "Core.h"
#include "Model.h"


class Shader
{
public:
	Shader() {};
	Shader(const std::string& filename_v, const std::string& filename_f)
	{
		loadShader(filename_v, filename_f);
	}
	~Shader();
	
	void createShader(const std::string& vertexShader, const std::string& fragmentShader);
	void loadShader(const std::string& filename_v, const std::string& filename_f);

	void bind();

	void setUniformM4f(const std::string& name, glm::mat4& matrix);
	void setUniformVec3f(const std::string& name, glm::vec3 vec);
	void setUniformVec3f(const std::string& name, float data[3]);
	void setUniform1f(const std::string& name, float f);
	void setUniformMaterial(const std::string& name, Material& mat);

private:

	int getUniformLocation(const std::string& name);

	unsigned int compileShader(const std::string& source, unsigned int type);
	//void createShader(const std::string& vertexShader, const std::string& fragmentShader);

private:

	std::unordered_map<std::string, int> cachedUniforms;

	unsigned int programID;
	unsigned int vertexID;
	unsigned int fragmentID;
};

