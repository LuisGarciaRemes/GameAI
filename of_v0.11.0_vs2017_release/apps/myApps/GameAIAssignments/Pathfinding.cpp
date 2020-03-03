#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
	m_pathIndex = 0;
}

Pathfinding::~Pathfinding()
{
}

void Pathfinding::ResetPathIndex()
{
	m_pathIndex = 0;
}

MovementAlgorithms::Steering Pathfinding::SeekingPath(Kinematic * i_char, std::vector<int> i_path, float i_distanceFromNode, float i_maxLinear, float i_targetRadius, float i_slowRadius, float i_maxAngular, float i_maxRot)
{
	MovementAlgorithms::Steering temp;

	if ()
	{

	}

	temp.m_linear = ;
	temp.m_angular = ;


	return temp;
}

