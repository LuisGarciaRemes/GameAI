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
	static MovementAlgorithms::Steering* DynamicSeek(Kinematic* i_char, Kinematic* i_target, float i_maxLinear);
	static MovementAlgorithms::Steering* Align(Kinematic * i_char, Kinematic * i_target, float i_targetRadius,float i_slowRadius, float i_maxAngular, float i_maxRot);
	static MovementAlgorithms::Steering* LookWhereYouAreGoing(Kinematic * i_char, float i_targetRadius, float i_slowRadius, float i_maxAngular, float i_maxRot);
	static MovementAlgorithms::Steering* Face(Kinematic * i_char, Kinematic * i_target, float i_targetRadius, float i_slowRadius, float i_maxAngular, float i_maxRot);
	static MovementAlgorithms::Steering* DynamicArrive(Kinematic* i_char, Kinematic* i_target, float i_maxLinear, float i_targetRadius, float i_slowRadius);
	static MovementAlgorithms::Steering* DynamicWander(Kinematic* i_char, float& i_wanderOrientation, float i_wanderOffset, float i_wanderRadius, float i_wanderRate, float i_maxAngular,float i_maxLinear);
	static MovementAlgorithms::Steering* Separation(Kinematic* i_char, std::vector<Kinematic*> i_targets, float i_threshold, float decayCoefficient, float i_axLinear);
	static MovementAlgorithms::Steering* VelocityMatch(Kinematic* i_char, Kinematic* i_target, float i_maxLinear);
private:
	
};

