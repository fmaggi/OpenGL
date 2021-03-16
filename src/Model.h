#pragma once

#include "Core.h"

struct Material
{
	float ns;
	float ka[3];
	float ks[3];
	float kd[3];
	float ke[3];
	float ni;
	float d;
	float illum;
};


class ObjModel
{
public:

	ObjModel() = default;
	~ObjModel();

	void storeIndices(std::vector<unsigned int>& indices);

	inline unsigned int getIbo() { return ibo; }
	inline unsigned int getVertexCount() { return vertexCount; }

	inline const std::string& getMaterial() const { return m_Material; }
	inline void storeMaterial(std::string material) { m_Material = material; }

private:
	unsigned int ibo;
	unsigned int vertexCount;
	std::string m_Material;
};

class Model
{
public:
	Model();
	~Model();

	inline unsigned int getVaoID() { return vaoID; }

	void storeData(const void* data, unsigned int count, unsigned int vertices);
	void storeData(std::vector<Vertex>& data);

	void storeObj(std::vector<unsigned int>& model, std::string material);

	void storeMaterial(Material& material, std::string& materialName);
	Material& getMaterial(const std::string& name);

	inline std::vector<ObjModel*>& getMeshes() { return meshes; }
	inline unsigned int getAttribs() { return attribCounter; }

private:
	unsigned int vaoID;
	std::vector<unsigned int> buffers;
	unsigned int attribCounter;
	unsigned int m_Stride;
	unsigned int offset;

	std::unordered_map<std::string, Material> materials;

	std::vector<ObjModel*> meshes;
};

