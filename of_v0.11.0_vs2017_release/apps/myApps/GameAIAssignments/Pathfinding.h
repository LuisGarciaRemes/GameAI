#pragma once
#include "MovementAlgorithms.h"
#include "SearchAlgorithms.h"

class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();
	void ResetPathIndex();
	MovementAlgorithms::Steering ArrivePath(Kinematic * i_char, std::vector<int> i_path, SearchAlgorithms::Grid i_grid, float i_distanceFromNode, float i_maxLinear, float i_targetRadiusLinear, float i_targetRadiusAngular, float i_slowRadiusLinear, float i_slowRadiusAngular, float i_maxAngular, float i_maxRot);
	
private:
	int m_pathIndex;
};

