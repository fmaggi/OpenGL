#pragma once
#include "Core.h"


class BaseObject
{
public:
	virtual inline void setPosition(glm::vec3&& position) = 0;
	virtual inline glm::vec3 getPosition() const = 0;
	virtual inline void move(glm::vec3 d) = 0;

	virtual inline void setRotation(glm::vec3&& rot) = 0;
	virtual inline glm::vec3 getRotation() const = 0;
	virtual inline void rotate(glm::vec3 d) = 0;
};

