#pragma once
#include "Kinematic.h"

class Boid
{

	struct Triangle
	{
		ofVec2f point1;
		ofVec2f point2;
		ofVec2f point3;
	};

public:
	Boid(float i_x, float i_y, float i_orientation, float i_radius);
	~Boid();
	Kinematic* GetKinematic();
	float GetRadius();
	Boid::Triangle* GetTriangle();
	void Update();
private:
	Kinematic* m_kinematic;
	float m_radius;
	Boid::Triangle* triangle;
	void UpdateTriangleVertices();
	float prevOrientation;

};

