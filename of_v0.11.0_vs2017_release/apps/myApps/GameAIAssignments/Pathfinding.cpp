#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
	m_pathIndex = 1;
}

Pathfinding::~Pathfinding()
{
}

void Pathfinding::ResetPathIndex()
{
	m_pathIndex = 1;
}

MovementAlgorithms::Steering Pathfinding::ArrivePath(Kinematic * i_char, std::vector<int> i_path, SearchAlgorithms::Grid i_grid, float i_distanceFromNode, float i_maxLinear, float i_targetRadiusLinear, float i_targetRadiusAngular, float i_slowRadiusLinear, float i_slowRadiusAngular, float i_maxAngular, float i_maxRot)
{
	MovementAlgorithms::Steering temp;
	Kinematic *target = new Kinematic();

	ofVec2f targetPos = i_grid.GetCenterOfNode(i_path[m_pathIndex]);

	ofVec2f distanceVector = targetPos - i_char->GetPosition();

	float distance = distanceVector.length();

	target->SetPosition(targetPos);

	std::cout << "going to node " << i_path[m_pathIndex] <<"\n";
	std::cout << "distance is " << distance << "\n";

	temp.m_linear = MovementAlgorithms::DynamicArrive(i_char, target, i_maxLinear, i_targetRadiusLinear, i_slowRadiusLinear)->m_linear;
	temp.m_angular = MovementAlgorithms::LookWhereYouAreGoing(i_char, i_targetRadiusAngular, i_slowRadiusAngular, i_maxAngular, i_maxRot)->m_angular;

	if (m_pathIndex < i_path.size()-1 && distance <= i_distanceFromNode)
	{
		m_pathIndex++;
	}

	return temp;
}

