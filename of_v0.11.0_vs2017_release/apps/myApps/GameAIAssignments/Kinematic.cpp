#include "Kinematic.h"

ofVec2f Kinematic::GetPosition()
{
	return m_position;
}

ofVec2f Kinematic::GetVelocity()
{
	return m_velocity;
}

float Kinematic::GetOrientation()
{
	return m_orientation;
}

float Kinematic::GetRotation()
{
	return m_rotation;
}

Kinematic::Kinematic(float i_x, float i_y, float i_orientation)
{
	m_position.set(i_x,i_y);
	m_velocity.set(0.0f,0.0f);
	m_orientation = i_orientation;
	m_rotation = 0.0f;
}

Kinematic::~Kinematic()
{
}
