#pragma once
#include "Model.h"
#include "Core.h"
#include "BaseObject.h"

class Entity : public BaseObject
{
public:

	Entity();
	~Entity();

	void launch();

	inline void setPosition(glm::vec3&& position) override { m_Position = position; }
	inline glm::vec3 getPosition() const override { return m_Position; }
	inline void move(glm::vec3 d) override { m_Position += d; }

	inline void setRotation(glm::vec3&& rot) override { m_Rotation = rot; }
	inline glm::vec3 getRotation() const override { return m_Rotation; }
	inline void rotate(glm::vec3 d) override { m_Rotation += d; }

	inline void setScale(float scale) { m_Scale = glm::vec3(scale); }
	inline glm::vec3 getScale() const { return m_Scale; }
	inline void scale(float d) { m_Scale += glm::vec3(d); }

	inline void setModel(Model* model) { m_Model = model; }
	inline Model* getModel() const { return m_Model; }

	inline glm::vec2 getSpeed() { return m_Speed; }
	inline void setSpeed(float sx, float sy) { m_Speed.x = sx; m_Speed.y = sy; }

	inline float getMass() { return m_Mass; }
	inline float getPower() { return m_Power; }

	const inline glm::mat4& getTransformationMatrix() const { return m_transformation; }
	void calculateTransformationMatrix();

private:
	Model* m_Model;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	glm::vec2 m_Speed;
	float m_Mass;
	float m_Power;
	float m_Acceleration;

	glm::mat4 m_transformation;
};

