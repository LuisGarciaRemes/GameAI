#pragma once
#include "ofVec2f.h"
#include <math.h>

class Kinematic
{
public:
	ofVec2f GetPosition();
	ofVec2f GetVelocity();
	ofVec2f GetLinear();
	void SetPosition(ofVec2f i_pos);
	void SetVelocity(ofVec2f i_vel);
	void SetLinear(ofVec2f i_linear);
	void SetAngular(float i_angular);
	void SetRotation(float i_rot);
	void SetOrientation(float i_z);
	float GetOrientation();
	float GetRotation();
	float GetAngular();
	Kinematic(float i_x, float i_y, float i_orientation);
	Kinematic();
	~Kinematic();

	void UpdateKinematic(float dT);

	//basic-motion
	int m_basicMotionIndex = 0;

	float  m_maxSpeed;

private:
	float m_orientation;
	ofVec2f m_position;
	ofVec2f m_velocity;

	float m_rotation;

	ofVec2f m_linear;
	float m_angular;
};

