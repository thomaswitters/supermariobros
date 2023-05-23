#include "pch.h"
#include "Hud.h"
#include <iostream>


Hud::Hud(const Point2f& topLeft, float totalTime, int level, int lives, int coins, int score)
	: m_BottomLeft{ topLeft }
	, m_TotalTime{ totalTime }
	, m_Level{level}
	, m_Lives{lives}
	, m_Coins{coins}
	, m_Score{score}
	, m_pTextFont{}
	, m_pHudFont{}
	, m_pTextTime{}
	, m_pTextLevel{}
	, m_pTextLives{}
	, m_pTextMario{}
	, m_pCoinTexture{ new Texture("Images/coin.png") }
	, m_pSettingsTexture{new Texture("Images/settings2.png")}
	, m_PosCoin{ m_BottomLeft.x - 266, m_BottomLeft.y - 50 }
	, m_pTextX{}
	, m_pCoins{}
	, m_pSettingsScreen{new SettingsScreen()}
	, m_HasOpenSettings{false}
{
	m_pTextFont = TTF_OpenFont("Fonts/Inconsolata-ExtraLight.ttf", 32);
	m_pHudFont = TTF_OpenFont("Fonts/Inconsolata-ExtraBold.ttf", 28);

	//m_pCoins = new Texture("00", m_pHudFont, Color4f{ 1,1,1,1 });
	m_pTextX = new Texture("X", m_pTextFont, Color4f{ 1,1,1,1 });
	m_pTextTime = new Texture("TIME", m_pHudFont, Color4f{ 1,1,1,1 });
	m_pTextLevel = new Texture("LEVEL", m_pHudFont, Color4f{ 1,1,1,1 });
	m_pTextLives = new Texture("LIVES", m_pHudFont, Color4f{ 1,1,1,1 });
	m_pTextMario = new Texture("MARIO", m_pHudFont, Color4f{ 1,1,1,1 });
	
	//m_pTextTimeCount = new Texture(m_TextTimeCount, m_pHudFont, Color4f{ 1,1,1,1 });

}

Hud::~Hud()
{
	//delete m_pTextTimeCount;
	delete m_pTextX;
	//delete m_pCoins;
	delete m_pCoinTexture;
	delete m_pSettingsTexture;
	delete m_pTextTime;
	delete m_pTextLevel;
	delete m_pTextLives;
	delete m_pTextMario;
	TTF_CloseFont(m_pHudFont);
	delete m_pSettingsScreen;
}

void Hud::Draw()
{
	if (!m_HasOpenSettings)
	{
		float sourceWidthCoin{ m_pCoinTexture->GetWidth() };
		float sourceHeightCoin{ m_pCoinTexture->GetHeight() };
		Rectf dstCoin{ m_PosCoin.x, m_PosCoin.y,sourceWidthCoin, sourceHeightCoin };
		m_pCoinTexture->Draw(dstCoin);


		float sourceWidthSettings{ m_pSettingsTexture->GetWidth() / 10 };
		float sourceHeightSettings{ m_pSettingsTexture->GetHeight() / 10 };
		Rectf dstSetttings{ m_BottomLeft.x + 280, m_BottomLeft.y - 55,sourceWidthSettings, sourceHeightSettings };
		m_pSettingsTexture->Draw(dstSetttings);
		Rectf dstX{ m_BottomLeft.x - 249.f, m_BottomLeft.y - 55, 10.f, 25 };
		m_pTextX->Draw(dstX);

		m_pTextTime->Draw(Point2f(m_BottomLeft.x + 30, m_BottomLeft.y - 35));
		m_pTextLevel->Draw(Point2f(m_BottomLeft.x - 130, m_BottomLeft.y - 35));
		m_pTextLives->Draw(Point2f(m_BottomLeft.x + 170, m_BottomLeft.y - 35));
		m_pTextMario->Draw(Point2f(m_BottomLeft.x - 420, m_BottomLeft.y - 35));
		TextureHelper::DrawInt((int)m_TotalTime, Point2f(m_BottomLeft.x + 37, m_BottomLeft.y - 55), m_pHudFont);
		TextureHelper::DrawInt(m_Level, Point2f(m_BottomLeft.x - 102, m_BottomLeft.y - 55), m_pHudFont);
		TextureHelper::DrawInt(m_Lives, Point2f(m_BottomLeft.x + 199, m_BottomLeft.y - 55), m_pHudFont);
		TextureHelper::DrawInt(m_Coins, Point2f(m_BottomLeft.x - 232.f, m_BottomLeft.y - 55), m_pHudFont);
		TextureHelper::DrawInt(m_Score, Point2f(m_BottomLeft.x - 420, m_BottomLeft.y - 55), m_pHudFont);
	}
	else if (m_HasOpenSettings)
	{
		m_pSettingsScreen->Draw();
	}
}

void Hud::Update(float elapsedSec, GameState* gameState)
{
	m_pSettingsScreen->Update(elapsedSec, gameState);
	m_TotalTime -= elapsedSec; 
	m_Lives = gameState->GetAmountOfLives();
	m_Coins = gameState->GetAmountCoins();
}

void Hud::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (m_HasOpenSettings)
	{
		m_pSettingsScreen->ProcessMouseUpEvent(e, m_HasOpenSettings);
	}

	if (!m_HasOpenSettings)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
		{
			if (e.x >= m_BottomLeft.x + 280.f && e.y >= m_BottomLeft.y - 55 && e.x <= m_BottomLeft.x + 325.f && e.y <= m_BottomLeft.y - 10)
			{
				m_HasOpenSettings = true;
			}
			break;
		}
		}
	}
}

void Hud::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	if (m_HasOpenSettings)
	{
		m_pSettingsScreen->ProcessMouseDownEvent(e, m_HasOpenSettings);
	}
}

void Hud::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	if (m_HasOpenSettings)
	{
		m_pSettingsScreen->ProcessMouseMotionEvent(e);
	}
}

void Hud::SetCloseSettings()
{
	m_HasOpenSettings = false;
}