#pragma once
#include "vendor/glm/glm.hpp"

class CircleUnit
{
public:
	CircleUnit(glm::vec2 pos, float size) :m_pos(pos), m_size(size) {}
	~CircleUnit() {}

	float* getSize() { return &m_size; }
	glm::vec2* getPos() { return &m_pos; }
	void setPos(glm::vec2 pos) { this->m_pos = pos; }
	void setSize(float size) { this->m_size = size; }

private:
	glm::vec2 m_pos;
	float m_size;
};