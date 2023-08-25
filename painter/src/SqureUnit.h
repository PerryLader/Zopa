#pragma once
#include "vendor/glm/glm.hpp"

class SqureUnit
{
public:
	SqureUnit(glm::vec2 pos, float size) :m_pos(pos), m_size(size) {}
	~SqureUnit() {}

	float* getSize() { return &m_size; }
	glm::vec2 *getPos() { return &m_pos; }
	void setPos(glm::vec2 pos) { this->m_pos = pos; }
	void setSize(float size) { this->m_size = size; }

private:
	glm::vec2 m_pos;
	float m_size;
};