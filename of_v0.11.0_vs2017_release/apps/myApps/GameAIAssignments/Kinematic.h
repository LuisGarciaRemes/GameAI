#pragma once
#include "ofVec2f.h"
#include <math.h>

class Kinematic
{
public:
	ofVec2f GetPosition();
	ofVec2f GetVelocity();
	void SetPosition(ofVec2f i_pos);
	void SetVelocity(ofVec2f i_vel);
	void SetOrientation(float i_z);
	float GetOrientation();
	float GetRotation();
	Kinematic(float i_x, float i_y, float i_orientation);
	~Kinematic();

	void UpdateKinematic(float dT);

private:
	ofVec2f m_position;
	ofVec2f m_velocity;
	ofVec2f m_linear;
	float m_angular;
	float m_orientation;
	float m_rotation;
};

