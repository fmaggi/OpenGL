#pragma once
#include "Model.h"
#include "Core.h"

class Entity
{
public:

	Entity();
	~Entity();

	void update(float timestep);
	void launch();

	inline void setPosition(glm::vec3 position) { m_Position = position; }
	inline glm::vec3 getPosition() const { return m_Position; }
	inline void move(glm::vec3 d, float(ts)) { m_Position += d * glm::vec3(ts); }

	inline void setRotation(glm::vec3 rot) { m_Rotation = rot; }
	inline glm::vec3 getRotation() const { return m_Rotation; }
	inline void rotate(glm::vec3 d, float ts) { m_Rotation += d * glm::vec3(ts); }

	inline void setScale(float scale) { m_Scale = glm::vec3(scale); }
	inline glm::vec3 getScale() const { return m_Scale; }
	inline void scale(float d, float ts) { m_Scale += glm::vec3(d) * glm::vec3(ts); }

	inline void setModel(Model* model) { m_Model = model; }
	inline Model* getModel() const { return m_Model; }

	glm::mat4 getTransformationMatrix();

private:
	Model* m_Model;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	float m_Speed;
	float m_Mass;
	float m_Power;
	float m_Acceleration;
};

