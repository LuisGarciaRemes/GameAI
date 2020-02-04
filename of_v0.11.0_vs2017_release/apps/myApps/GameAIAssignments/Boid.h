#pragma once
#include "Kinematic.h"
#include <vector>

class Boid
{

	struct Triangle
	{
		ofVec2f point1;
		ofVec2f point2;
		ofVec2f point3;
	};

public:

	struct Breadcrumb
	{
		ofVec2f pos;
	};

	Boid(float i_x, float i_y, float i_orientation, float i_radius, float i_mass);
	~Boid();
	Kinematic* GetKinematic();
	float GetRadius();
	Boid::Triangle* GetTriangle();
	void Update(float dT);
	void SetDropRate(float i_rate);
	std::vector<Boid::Breadcrumb> GetCrumbs();

	void ClearBreadCrumbs();

private:
	Kinematic* m_kinematic;
	float m_radius;
	Boid::Triangle* m_triangle;
	void UpdateTriangleVertices();
	float m_dropRate;
	float m_dropTimer;
	std::vector<Breadcrumb>  m_breadCrumbs;
	void DropBreadCrumb(float dT);

};

