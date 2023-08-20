#include "Object2D.h"

int Object2D::GetX() const
{
	return m_x;
}

int Object2D::GetY() const
{
	return m_y;
}

void Object2D::SetX(int x)
{
	m_x = x;
}

void Object2D::SetY(int y)
{
	m_y = y;
}