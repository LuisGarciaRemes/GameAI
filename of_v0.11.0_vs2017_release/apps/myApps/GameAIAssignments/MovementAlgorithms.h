#pragma once
#include "Kinematic.h"

class MovementAlgorithms
{
public:
	struct Steering
	{
		ofVec2f m_linear = ofVec2f(0.0f,0.0f);
		float m_angular = 0.0f;
	};

	static void BasicMotion(Kinematic* i_kinematic);
	static void SetOrientationBasedOnDirection(Kinematic* i_kinematic);
	static MovementAlgorithms::Steering DynamicSeek(Kinematic* i_kinematic, ofVec2f target, float maxAccel);

private:
	
};

