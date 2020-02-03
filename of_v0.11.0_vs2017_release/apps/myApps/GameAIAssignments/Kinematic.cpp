#include "Kinematic.h"

ofVec2f Kinematic::GetPosition()
{
	return m_position;
}

ofVec2f Kinematic::GetVelocity()
{
	return m_velocity;
}

ofVec2f Kinematic::GetLinear()
{
	return m_linear;
}

void Kinematic::SetPosition(ofVec2f i_pos)
{
	m_position = i_pos;
}

void Kinematic::SetVelocity(ofVec2f i_vel)
{
	m_velocity = i_vel;
}

void Kinematic::SetLinear(ofVec2f i_linear)
{
	m_linear = i_linear;
}

void Kinematic::SetAngular(float i_angular)
{
	m_angular = i_angular;
}

void Kinematic::SetRotation(float i_rot)
{
	m_rotation = i_rot;
}

void Kinematic::SetOrientation(float i_z)
{
	m_orientation = i_z;
}

float Kinematic::GetOrientation()
{
	return m_orientation;
}

float Kinematic::GetRotation()
{
	return m_rotation;
}

float Kinematic::GetAngular()
{
	return m_angular;
}

Kinematic::Kinematic(float i_x, float i_y, float i_orientation)
{
	m_position.set(i_x,i_y);
	m_velocity.set(0.0f,0.0f);
	m_orientation = i_orientation;
	m_rotation = 0.0f;
	m_maxSpeed = 150.0f;
	m_angular = 0.0f;
	m_linear.set(0.0f, 0.0f);
}

Kinematic::Kinematic()
{
	m_position.set(0.0f, 0.0f);
	m_velocity.set(0.0f, 0.0f);
	m_orientation = 0.0f;
	m_rotation = 0.0f;
	m_maxSpeed = 150.0f;
	m_angular = 0.0f;
	m_linear.set(0.0f, 0.0f);
}

Kinematic::~Kinematic()
{
}

void Kinematic::UpdateKinematic(float dT)
{

	m_position += m_velocity * dT + m_linear * (0.5f)*(pow(dT,2));
	m_orientation += m_rotation * dT + m_angular * (0.5f)*(pow(dT, 2));

	m_velocity += m_linear * dT;
	m_rotation += m_angular * dT;

	if (m_velocity.length() > m_maxSpeed)
	{
		m_velocity.normalize();
		m_velocity *= m_maxSpeed;
	}
}
