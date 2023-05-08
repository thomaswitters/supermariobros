#include "pch.h"
#include "Hud.h"
#include <iostream>


Hud::Hud(const Point2f& topLeft, float totalTime)
	: m_BottomLeft{ topLeft }
	, m_TotalTime{ totalTime }
	, m_pHudFont{}
	, m_pTextTime{}
//	, m_pTextTimeCount{}
{
	m_pHudFont = TTF_OpenFont("Fonts/Inconsolata-ExtraBold.ttf", 28);
	const char* error = TTF_GetError();
	
	m_pTextTime = new Texture("Time", m_pHudFont, Color4f{ 1,1,1,1 });
	
	//m_pTextTimeCount = new Texture(m_TextTimeCount, m_pHudFont, Color4f{ 1,1,1,1 });

}

Hud::~Hud()
{
	
	//delete m_pTextTimeCount;
	delete m_pTextTime;
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
	m_pTextTime->Draw(Point2f(m_BottomLeft.x + 50, m_BottomLeft.y - 35));
	TextureHelper::DrawInt((int)m_TotalTime, Point2f(m_BottomLeft.x + 34.f + 50, m_BottomLeft.y - 55), m_pHudFont);

}

void Hud::Update(float elapsedSec)
{
	m_TotalTime -= elapsedSec*2;
}

