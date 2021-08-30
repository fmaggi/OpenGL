#include "Model.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Model::Model()
{
	glGenVertexArrays(1, &vaoID);
	attribCounter = 0;
	m_Stride = 0;
	offset = 0;
}

Model::~Model()
{
	for (auto obj : meshes)
	{
		delete obj;
	}
	for (unsigned int buffer : buffers)
	{
		glDeleteBuffers(1, &buffer);
	}
	glDeleteVertexArrays(1, &vaoID);
}

void Model::storeData(std::vector<Vertex>& data)
{
	glBindVertexArray(vaoID);
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	buffers.push_back(buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(attribCounter);
	glVertexAttribPointer(attribCounter, 3, GL_FLOAT, GL_FALSE, 0, 0);
	attribCounter++;
}

void Model::storeData(const void* data, unsigned int count, unsigned int vertices)
{
	glBindVertexArray(vaoID);
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	buffers.push_back(buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, count * vertices * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(attribCounter);
	glVertexAttribPointer(attribCounter, count, GL_FLOAT, GL_FALSE, 0, 0);
	attribCounter++;
}

void Model::storeObj(std::vector<unsigned int>& indices, std::string material)
{
	ObjModel* m_Model = new ObjModel;
	m_Model->storeIndices(indices);
	m_Model->storeMaterial(material);
	meshes.push_back(m_Model);
}

void Model::storeMaterial(Material& material, std::string& materialName)
{
	materials[materialName] = material;
}

Material& Model::getMaterial(const std::string& name)
{
	return materials[name];
}

ObjModel::~ObjModel()
{
	glDeleteBuffers(1, &ibo);
}

void ObjModel::storeIndices(std::vector<unsigned int>& indices)
{
	vertexCount = indices.size();
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}
