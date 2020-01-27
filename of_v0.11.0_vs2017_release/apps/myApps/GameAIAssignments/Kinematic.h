#pragma once
#include "ofVec2f.h"
#include <math.h>

class Kinematic
{
public:
	ofVec2f GetPosition();
	ofVec2f GetVelocity();
	float GetOrientation();
	float GetRotation();
	Kinematic(float i_x, float i_y, float i_orientation);
	~Kinematic();


private:
	ofVec2f m_position;
	ofVec2f m_velocity;
	float m_orientation;
	float m_rotation;
};

