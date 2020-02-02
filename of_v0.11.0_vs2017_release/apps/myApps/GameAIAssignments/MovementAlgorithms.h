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
	static void SnapToDirectionOfTravel(Kinematic* i_kinematic);
	static MovementAlgorithms::Steering* DynamicSeek(Kinematic* i_char, Kinematic* i_target, float maxAccel);
	static MovementAlgorithms::Steering* Align(Kinematic * i_char, Kinematic * i_target, float i_targetRadius,float i_slowRadius, float maxAngular, float maxRot);
	static MovementAlgorithms::Steering* LookWhereYouAreGoing(Kinematic * i_char, float i_targetRadius, float i_slowRadius, float maxAngular, float maxRot);
	static MovementAlgorithms::Steering* DynamicArrive(Kinematic* i_char, Kinematic* i_target, float maxAccel, float i_targetRadius, float i_slowRadius);

private:
	
};

