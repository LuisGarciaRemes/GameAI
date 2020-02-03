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

MovementAlgorithms::Steering* MovementAlgorithms::DynamicSeek(Kinematic * i_char, Kinematic * i_target, float maxAccel)
{
	MovementAlgorithms::Steering* steering = new MovementAlgorithms::Steering();

	steering->m_linear = i_target->GetPosition() - i_char->GetPosition();

	steering->m_linear = steering->m_linear.normalize();
	steering->m_linear *= maxAccel;

	steering->m_angular = 0;

	return steering;
}

MovementAlgorithms::Steering* MovementAlgorithms::Align(Kinematic * i_char, Kinematic * i_target, float i_targetRadius, float i_slowRadius, float i_maxAngular, float i_maxRot)
{
	MovementAlgorithms::Steering* result = new MovementAlgorithms::Steering();

	float rotation = i_target->GetOrientation() - i_char->GetOrientation();

	
	rotation = CLAMP(rotation,-PI,PI);

	float rotationSize = abs(rotation);
	float targetRotation;

	
	if (rotationSize > i_slowRadius)
	{
		targetRotation = i_maxRot;
	}
	else if (rotationSize < i_targetRadius)
	{
		targetRotation = 0.0f;
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
		return new MovementAlgorithms::Steering();
	}

	i_target->SetOrientation(atan2(vel.y,vel.x));

	return MovementAlgorithms::Align(i_char, i_target, i_targetRadius, i_slowRadius, maxAngular, maxRot);
}

MovementAlgorithms::Steering * MovementAlgorithms::DynamicArrive(Kinematic * i_char, Kinematic * i_target, float maxAccel, float i_targetRadius, float i_slowRadius)
{
	MovementAlgorithms::Steering* result = new MovementAlgorithms::Steering();

	ofVec2f direction = i_target->GetPosition() - i_char->GetPosition();	float distance = direction.length();	float targetSpeed;	ofVec2f targetVel;	
	if(distance > i_slowRadius)
	{
		targetSpeed = i_char->m_maxSpeed;
	}
	else if (distance < i_targetRadius)	{		targetSpeed = 0.0f;	}
	else
	{
		targetSpeed = i_char->m_maxSpeed * (distance / i_slowRadius);
	}

	targetVel = direction;
	targetVel = targetVel.normalize();
	targetVel *= targetSpeed;

	result->m_linear = targetVel - i_char->GetVelocity();
	result->m_linear /= 0.1f;

	if (result->m_linear.length() > maxAccel)
	{
		result->m_linear = result->m_linear.normalize();
		result->m_linear *= maxAccel;
	}

	result->m_angular = 0.0f;

	return result;
}


