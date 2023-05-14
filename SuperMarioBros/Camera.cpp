#include "pch.h"
#include "Camera.h"
#include <utils.h>

Camera::Camera(float width, float height) :
	m_Width{ width },
	m_Height{ height },
	m_LevelBoundaries{ 0.f, 0.f, width, height },
	m_LevelBoundaries2{ 0.f, 0.f, width, height }
{

}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::SetLevelBoundaries2(const Rectf& levelBoundaries)
{
	m_LevelBoundaries2 = levelBoundaries;
}

void Camera::Transform(const Point2f& target)
{
	Point2f newTarget = Track(target);
	if (newTarget.y >= 250)
	{
		Clamp(newTarget);
	}
	else
	{
		Clamp2(newTarget);
	}
	

	glTranslatef(-newTarget.x, -newTarget.y, 0.f);
	
}

Point2f Camera::Track(const Point2f& target) // target is peetie
{
	Rectf Camera{};

	Camera.left = target.x - m_Width / 2 + 20.f;
	Camera.bottom = target.y;

	return Point2f(Camera.left, Camera.bottom);
}


void Camera::Clamp(Point2f& bottomLeftPos)
{

	if (bottomLeftPos.x <= m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	if (bottomLeftPos.x + m_Width >= m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.y <= m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	if (bottomLeftPos.y + m_Height >= m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	}
}
void Camera::Clamp2(Point2f& bottomLeftPos)
{
	if (bottomLeftPos.x <= m_LevelBoundaries2.left)
	{
		bottomLeftPos.x = m_LevelBoundaries2.left;
	}
	if (bottomLeftPos.x + m_Width >= m_LevelBoundaries2.left + m_LevelBoundaries2.width)
	{
		bottomLeftPos.x = m_LevelBoundaries2.left + m_LevelBoundaries2.width - m_Width;
	}
	if (bottomLeftPos.y <= m_LevelBoundaries2.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries2.bottom;
	}
	if (bottomLeftPos.y + m_Height >= m_LevelBoundaries2.bottom + m_LevelBoundaries2.height)
	{
		bottomLeftPos.y = m_LevelBoundaries2.bottom + m_LevelBoundaries2.height - m_Height;
	}
}