#include "pch.h"
#include "Hud.h"
#include <iostream>


Hud::Hud(const Point2f& topLeft, float totalTime, int level, int lives)
	: m_BottomLeft{ topLeft }
	, m_TotalTime{ totalTime }
	, m_Level{level}
	, m_Lives{lives}
	, m_pHudFont{}
	, m_pTextTime{}
	, m_pTextLevel{}
	, m_pTextLives{}
//	, m_pTextTimeCount{}
{
	m_pHudFont = TTF_OpenFont("Fonts/Inconsolata-ExtraBold.ttf", 28);
	const char* error = TTF_GetError();
	
	m_pTextTime = new Texture("TIME", m_pHudFont, Color4f{ 1,1,1,1 });
	m_pTextLevel = new Texture("LEVEL", m_pHudFont, Color4f{ 1,1,1,1 });
	m_pTextLives = new Texture("LIVES", m_pHudFont, Color4f{ 1,1,1,1 });
	
	//m_pTextTimeCount = new Texture(m_TextTimeCount, m_pHudFont, Color4f{ 1,1,1,1 });

}

Hud::~Hud()
{
	
	//delete m_pTextTimeCount;
	delete m_pTextTime;
	delete m_pTextLevel;
	delete m_pTextLives;
	TTF_CloseFont(m_pHudFont);
}


class TextureHelper {
public:
	static void DrawInt(int IntValue, Point2f position, TTF_Font* pFont) {
		std::string str1 = std::to_string(IntValue);
		Texture* xTexture = new Texture(str1, pFont, Color4f{ 1,1,1,1 });
		xTexture->Draw(position);
		delete xTexture;
	}
};

void Hud::Draw()
{
//	m_pTextTimeHundersTexture->Draw(Point2f(m_BottomLeft.x + 8.f + 50, m_BottomLeft.y-55));
//	m_pTextTimeTentsTexture->Draw(Point2f(m_BottomLeft.x + 21.f + 50, m_BottomLeft.y-55));
//	m_pTextTimeNumbersTexture->Draw(Point2f(m_BottomLeft.x + 34.f + 50, m_BottomLeft.y-55));
	//m_pTextTimeCount->Draw(Point2f(m_BottomLeft.x, m_BottomLeft.y));
	m_pTextTime->Draw(Point2f(m_BottomLeft.x + 70, m_BottomLeft.y - 35));
	m_pTextLevel->Draw(Point2f(m_BottomLeft.x - 90, m_BottomLeft.y - 35));
	m_pTextLives->Draw(Point2f(m_BottomLeft.x + 220, m_BottomLeft.y - 35));
	TextureHelper::DrawInt((int)m_TotalTime, Point2f(m_BottomLeft.x + 77, m_BottomLeft.y - 55), m_pHudFont);
	TextureHelper::DrawInt(m_Level , Point2f(m_BottomLeft.x - 62, m_BottomLeft.y - 55), m_pHudFont);
	TextureHelper::DrawInt(m_Lives, Point2f(m_BottomLeft.x + 249, m_BottomLeft.y - 55), m_pHudFont);

}

void Hud::Update(float elapsedSec)
{
	m_TotalTime -= elapsedSec*2;
}

