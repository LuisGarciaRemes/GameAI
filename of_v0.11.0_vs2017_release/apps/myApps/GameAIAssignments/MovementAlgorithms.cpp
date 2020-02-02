#include "MovementAlgorithms.h"

void MovementAlgorithms::BasicMotion(Kinematic* i_kinematic)
{
	ofVec2f vel;

	switch (i_kinematic->m_basicMotionIndex)
	{
	case 0:
		if (i_kinematic->GetPosition().x >= 950.0f)
		{
			i_kinematic->m_basicMotionIndex = 1;
		}
		else
		{
			vel.set(100.0f, 0.0f);
		}
		break;
	case 1:
		if (i_kinematic->GetPosition().y <= 50.0f)
		{
			i_kinematic->m_basicMotionIndex = 2;
		}
		else
		{
			vel.set(0.0f, -100.0f);
		}
		break;
	case 2:
		if (i_kinematic->GetPosition().x <= 50.0f)
		{
			i_kinematic->m_basicMotionIndex = 3;
		}
		else
		{
			vel.set(-100.0f, 0.0f);
		}
		break;
	case 3:
		if (i_kinematic->GetPosition().y >= 700.0f)
		{
			i_kinematic->m_basicMotionIndex = 4;
		}
		else
		{
			vel.set(0.0f, 100.0f);
		}
		break;
	default:
		break;
	}

	i_kinematic->SetVelocity(vel);
	SetOrientationBasedOnDirection(i_kinematic);
}

void MovementAlgorithms::SetOrientationBasedOnDirection(Kinematic * i_kinematic)
{
	float ori;
	float z;

	z = pow(pow(i_kinematic->GetVelocity().x, 2) + pow(i_kinematic->GetVelocity().y, 2), .5);

	if (i_kinematic->GetVelocity().x == 0)
	{
		ori = asin(i_kinematic->GetVelocity().y / (z));
	}
	else
	{
		ori = acos(i_kinematic->GetVelocity().x / (z));
	}

	i_kinematic->SetOrientation(ori);
}

MovementAlgorithms::Steering MovementAlgorithms::DynamicSeek(Kinematic * i_kinematic, ofVec2f target, float maxAccel)
{
	MovementAlgorithms::Steering steering;

	steering.m_linear = target - i_kinematic->GetPosition();

	steering.m_linear.normalize();
	steering.m_linear * maxAccel;

	steering.m_angular = 0;

	return steering;
}


