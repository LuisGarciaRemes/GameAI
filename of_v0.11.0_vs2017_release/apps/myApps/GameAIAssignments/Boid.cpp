#include "Boid.h"

Boid::Boid(float i_x, float i_y,float i_orientation, float i_radius)
{
	m_kinematic = new Kinematic(i_x,i_y,i_orientation);
	m_radius = i_radius;
	triangle = new Triangle();
	triangle->point1.set(i_x,i_y + i_radius);
	triangle->point2.set(i_x, i_y - i_radius);
	triangle->point3.set(i_x+(2*i_radius),i_y);
	prevOrientation = 0.0f;
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
	return triangle;
}

void Boid::Update()
{

	//changes triangle vertices based on orientation
	if (prevOrientation != m_kinematic->GetOrientation())
	{
		UpdateTriangleVertices();
	}
}

void Boid::UpdateTriangleVertices()
{
	//change the rotation point to origin
	triangle->point1.set(triangle->point1.x - m_kinematic->GetPosition().x, triangle->point1.y - m_kinematic->GetPosition().y);
	triangle->point2.set(triangle->point2.x - m_kinematic->GetPosition().x, triangle->point2.y - m_kinematic->GetPosition().y);
	triangle->point3.set(triangle->point3.x - m_kinematic->GetPosition().x, triangle->point3.y - m_kinematic->GetPosition().y);

	//rotate the points of the triangle
	triangle->point1.set(triangle->point1.x *cos(m_kinematic->GetOrientation()-prevOrientation)- triangle->point1.y*sin(m_kinematic->GetOrientation() - prevOrientation), triangle->point1.y *cos(m_kinematic->GetOrientation() - prevOrientation) + triangle->point1.x*sin(m_kinematic->GetOrientation() - prevOrientation));
	triangle->point2.set(triangle->point2.x *cos(m_kinematic->GetOrientation() - prevOrientation) - triangle->point2.y*sin(m_kinematic->GetOrientation() - prevOrientation), triangle->point2.y *cos(m_kinematic->GetOrientation() - prevOrientation) + triangle->point2.x*sin(m_kinematic->GetOrientation() - prevOrientation));
	triangle->point3.set(triangle->point3.x *cos(m_kinematic->GetOrientation() - prevOrientation) - triangle->point3.y*sin(m_kinematic->GetOrientation() - prevOrientation), triangle->point3.y *cos(m_kinematic->GetOrientation() - prevOrientation) + triangle->point3.x*sin(m_kinematic->GetOrientation() - prevOrientation));
	
	//place points back where they were
	triangle->point1.set(triangle->point1.x + m_kinematic->GetPosition().x, triangle->point1.y + m_kinematic->GetPosition().y);
	triangle->point2.set(triangle->point2.x + m_kinematic->GetPosition().x, triangle->point2.y + m_kinematic->GetPosition().y);
	triangle->point3.set(triangle->point3.x + m_kinematic->GetPosition().x, triangle->point3.y + m_kinematic->GetPosition().y);

	//set the last orientation
	prevOrientation = m_kinematic->GetOrientation();
}
