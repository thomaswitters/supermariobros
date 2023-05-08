#pragma once
#include <Texture.h>
class Hud
{
public:
	Hud(const Point2f& topLeft, float totalTime, int level, int lives);
	~Hud();
	void Draw();
	void Update(float elapsedSec);

private:
	Point2f m_BottomLeft;
	float m_TotalTime;
	int m_Level;
	int m_Lives;
	TTF_Font* m_pHudFont;
//	Texture* m_pTextTimeCount;
	Texture* m_pTextTime;
	Texture* m_pTextLevel;
	Texture* m_pTextLives;
};

