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
}

void MovementAlgorithms::SnapToDirectionOfTravel(Kinematic * i_kinematic)
{
	i_kinematic->SetOrientation(atan2(i_kinematic->GetVelocity().y, i_kinematic->GetVelocity().x));
}

MovementAlgorithms::Steering* MovementAlgorithms::DynamicSeek(Kinematic * i_kinematic, ofVec2f target, float maxAccel)
{
	MovementAlgorithms::Steering* steering = new MovementAlgorithms::Steering();

	steering->m_linear = target - i_kinematic->GetPosition();

	steering->m_linear.normalize();
	steering->m_linear *= maxAccel;

	steering->m_angular = 0;

	return steering;
}

MovementAlgorithms::Steering* MovementAlgorithms::Align(Kinematic * i_char, Kinematic * i_target, float i_targetRadius, float i_slowRadius, float i_maxAngular, float i_maxRot)
{
	MovementAlgorithms::Steering* result = new MovementAlgorithms::Steering();

	float rotation = i_target->GetOrientation() - i_char->GetOrientation();

	
	if (rotation > PI)
	{
		rotation = PI;
	}
	else if(rotation < -PI)
	{
		rotation = -PI;
	}

	float rotationSize = abs(rotation);
	float targetRotation;

	if (rotationSize < i_targetRadius)
	{
		return nullptr;
	}

	if (rotationSize > i_slowRadius)
	{
		targetRotation = i_maxRot;
	}
	else
	{
		targetRotation = i_maxRot * rotationSize / i_slowRadius;
	}

	targetRotation *= rotation / rotationSize;

	result->m_angular = targetRotation - i_char->GetRotation();
	result->m_angular /= 0.1f;

	float angularAcceleration = abs(result->m_angular);

		if(angularAcceleration > i_maxAngular)
		{
			result->m_angular /= angularAcceleration;
			result->m_angular *= i_maxAngular;
		}
		
		result->m_linear = ofVec2f(0.0f,0.0f);

	return result;
}

MovementAlgorithms::Steering* MovementAlgorithms::LookWhereYouAreGoing(Kinematic * i_char, float i_targetRadius, float i_slowRadius, float maxAngular, float maxRot)
{
	Kinematic* i_target = new Kinematic(0.0f, 0.0f, 0.0f);

	ofVec2f vel = i_char->GetVelocity();

	if (vel.length() == 0)
	{
		return nullptr;
	}

	i_target->SetOrientation(atan2(vel.y,vel.x));

	return MovementAlgorithms::Align(i_char, i_target, i_targetRadius, i_slowRadius, maxAngular, maxRot);
}


