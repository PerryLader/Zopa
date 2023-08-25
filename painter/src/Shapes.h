#pragma once
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "vendor/glm/glm.hpp"
#include <vector>
#include "SqureUnit.h"
#include "CircleUnit.h"


 
class Squres
{
public:
	Squres() {}
	~Squres(){}
	void AddSqure(SqureUnit s)
	{
		m_squresCount++;
		m_SquresArray.push_back(s);
	}

	int m_squresCount=0;
	std::vector<SqureUnit> m_SquresArray;

	
	
};
class Circles
{
public:
	Circles() {}
	~Circles() {}
	void AddCircle(CircleUnit c)
	{
		m_circlesCount++;
		m_CirclesArray.push_back(c);
	}

	int m_circlesCount = 0;
	std::vector<CircleUnit> m_CirclesArray;

};


class Shapes
{
public:
	Shapes() {}
	~Shapes(){}

	Squres m_squres;
	Circles m_circles;
};

extern Shapes Allshapes;