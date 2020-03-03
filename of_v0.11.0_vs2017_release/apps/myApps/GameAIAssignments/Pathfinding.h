#pragma once
#include "MovementAlgorithms.h"
class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();

	void ResetPathIndex();
	

private:
	int m_pathIndex;
	MovementAlgorithms::Steering SeekingPath(Kinematic* i_char, std::vector<int> i_path, float i_distanceFromNode ,float i_maxLinear, float i_targetRadius, float i_slowRadius, float i_maxAngular, float i_maxRot);
};

