#include "pch.h"
#include "Camera.h"
#include <utils.h>

Camera::Camera(float width, float height) :
	m_Width{ width },
	m_Height{ height },
	m_LevelBoundaries{ 0.f, 0.f, width, height }
{

}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Point2f& target)
{
	Point2f newTarget = Track(target);
	Clamp(newTarget);

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