#pragma once
#include <Texture.h>
class Hud
{
public:
	Hud(const Point2f& topLeft, float totalTime);
	~Hud();
	void Draw();
	void Update(float elapsedSec);

private:
	Point2f m_BottomLeft;
	float m_TotalTime;
	TTF_Font* m_pHudFont;
//	Texture* m_pTextTimeCount;
	Texture* m_pTextTime;
};

