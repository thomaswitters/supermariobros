#pragma once
class Camera
{
public:
	Camera(float width, float height);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Point2f& target);

private:
	Point2f Track(const Point2f& target);
	void Clamp(Point2f& bottomLeftPos);

	float m_Width{};
	float m_Height{};
	Rectf m_LevelBoundaries{};

};

