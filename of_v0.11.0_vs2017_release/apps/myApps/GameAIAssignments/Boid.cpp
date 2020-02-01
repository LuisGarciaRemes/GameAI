#include "Boid.h"
#include "Kinematic.h"
#include "ofLog.h"
#include "ofUtils.h"

Boid::Boid(float i_x, float i_y,float i_orientation, float i_radius)
{
	m_kinematic = new Kinematic(i_x,i_y,i_orientation);
	m_radius = i_radius;
	m_triangle = new Triangle();
	m_triangle->point1.set(i_x,i_y + i_radius);
	m_triangle->point2.set(i_x, i_y - i_radius);
	m_triangle->point3.set(i_x+(2*i_radius),i_y);
	m_dropTimer = 0.0f;
	m_dropRate = 1.0f;

	Breadcrumb crumb;
	crumb.pos = ofVec2f(GetKinematic()->GetPosition());
	m_breadCrumbs.push_back(crumb);
}

Boid::~Boid()
{
}

Kinematic * Boid::GetKinematic()
{
	return m_kinematic;
}

float Boid::GetRadius()
{
	return m_radius;
}

Boid::Triangle * Boid::GetTriangle()
{
	return m_triangle;
}

void Boid::Update(float dT)
{
	m_kinematic->UpdateKinematic(dT);
	UpdateTriangleVertices();
	DropBreadCrumb(dT);

}

void Boid::SetDropRate(float i_rate)
{
	m_dropRate = i_rate;
}

std::vector<Boid::Breadcrumb> Boid::GetCrumbs()
{
	return m_breadCrumbs;
}

void Boid::BasicMotion()
{
	ofVec2f vel;

	switch (m_basicMoitionIndex)
	{
		case 0:
			if(GetKinematic()->GetPosition().x >= 700.0f)
			{
				m_basicMoitionIndex = 1;
			}
			else
			{
				ofLog(OF_LOG_NOTICE, "should be 0 " + ofToString(m_kinematic->GetOrientation()));
				vel.set(50.0f, 0.0f);
			}
			break;
		case 1: 
			if (GetKinematic()->GetPosition().y <= 50.0f)
			{
				m_basicMoitionIndex = 2;
			}
			else
			{
				ofLog(OF_LOG_NOTICE, "should be 4.71239 " + ofToString(m_kinematic->GetOrientation()));
				vel.set(0.0f, -50.0f);
			}
			break;
		case 2:
			if (GetKinematic()->GetPosition().x <= 50.0f)
			{
				m_basicMoitionIndex = 3;
			}
			else
			{
				ofLog(OF_LOG_NOTICE, "should be 3.14159 " + ofToString(m_kinematic->GetOrientation()));
				vel.set(-50.0f, 0.0f);
			}
			break;
		case 3:
			if (GetKinematic()->GetPosition().y >= 700.0f)
			{
				m_basicMoitionIndex = 4;
			}
			else
			{
				ofLog(OF_LOG_NOTICE, "should be 1.5708 " + ofToString(m_kinematic->GetOrientation()));
				vel.set(0.0f, 50.0f);
			}
			break;
		default :
			ClearBreadCrumbs();
			Breadcrumb crumb;
			crumb.pos = ofVec2f(GetKinematic()->GetPosition());
			m_breadCrumbs.push_back(crumb);
			m_dropTimer = 0.0f;
			m_basicMoitionIndex = 0;
			break;
	}

	GetKinematic()->SetVelocity(vel);	
	SetOrientationBasedOnDirection();
}

void Boid::SetOrientationBasedOnDirection()
{
	float ori;
	float z;

	z = pow(pow(GetKinematic()->GetVelocity().x, 2) + pow(GetKinematic()->GetVelocity().y, 2), .5);

	if (GetKinematic()->GetVelocity().x == 0)
	{
		ori = asin(GetKinematic()->GetVelocity().y / (z));
	}
	else
	{
		ori = acos(GetKinematic()->GetVelocity().x / (z));
	}

	GetKinematic()->SetOrientation(ori);	
}

void Boid::UpdateTriangleVertices()
{
	//update the points position
	m_triangle->point1.set(m_kinematic->GetPosition().x, m_kinematic->GetPosition().y + m_radius);
	m_triangle->point2.set(m_kinematic->GetPosition().x, m_kinematic->GetPosition().y - m_radius);
	m_triangle->point3.set(m_kinematic->GetPosition().x + (2 * m_radius), m_kinematic->GetPosition().y);

	//change the rotation point to origin
	m_triangle->point1.set(m_triangle->point1.x - m_kinematic->GetPosition().x, m_triangle->point1.y - m_kinematic->GetPosition().y);
	m_triangle->point2.set(m_triangle->point2.x - m_kinematic->GetPosition().x, m_triangle->point2.y - m_kinematic->GetPosition().y);
	m_triangle->point3.set(m_triangle->point3.x - m_kinematic->GetPosition().x, m_triangle->point3.y - m_kinematic->GetPosition().y);

	//rotate the points of the triangle
	m_triangle->point1.set(m_triangle->point1.x *cos(m_kinematic->GetOrientation())- m_triangle->point1.y*sin(m_kinematic->GetOrientation()), m_triangle->point1.y *cos(m_kinematic->GetOrientation()) + m_triangle->point1.x*sin(m_kinematic->GetOrientation()));
	m_triangle->point2.set(m_triangle->point2.x *cos(m_kinematic->GetOrientation()) - m_triangle->point2.y*sin(m_kinematic->GetOrientation()), m_triangle->point2.y *cos(m_kinematic->GetOrientation()) + m_triangle->point2.x*sin(m_kinematic->GetOrientation()));
	m_triangle->point3.set(m_triangle->point3.x *cos(m_kinematic->GetOrientation()) - m_triangle->point3.y*sin(m_kinematic->GetOrientation()), m_triangle->point3.y *cos(m_kinematic->GetOrientation()) + m_triangle->point3.x*sin(m_kinematic->GetOrientation()));
	
	//place points back where they were
	m_triangle->point1.set(m_triangle->point1.x + m_kinematic->GetPosition().x, m_triangle->point1.y + m_kinematic->GetPosition().y);
	m_triangle->point2.set(m_triangle->point2.x + m_kinematic->GetPosition().x, m_triangle->point2.y + m_kinematic->GetPosition().y);
	m_triangle->point3.set(m_triangle->point3.x + m_kinematic->GetPosition().x, m_triangle->point3.y + m_kinematic->GetPosition().y);
}

void Boid::DropBreadCrumb(float dT)
{
	if (m_dropTimer >= m_dropRate)
	{
		m_dropTimer = 0.0f;

		if (m_breadCrumbs[m_breadCrumbs.size()-1].pos != GetKinematic()->GetPosition())
		{
			Breadcrumb crumb;
			crumb.pos = ofVec2f(GetKinematic()->GetPosition());
			m_breadCrumbs.push_back(crumb);
		}
	}
	else
	{
		m_dropTimer += dT;
	}
}

void Boid::ClearBreadCrumbs()
{
	m_breadCrumbs.clear();
}
