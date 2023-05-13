#include "pch.h"
#include "LoadingScreen.h"
#include <utils.h>

LoadingScreen::LoadingScreen(BeginVieuw* beginScreen, int level, int lives)
	: m_pBeginScreen{beginScreen}
	, m_Time{2}
	, LoadGame{false}
	, m_pMarioTexture{new Texture("Images/normalMario3.png")}
	, m_PosMario{320.f, 200.f}
	, m_pCoinTexture{ new Texture("Images/coin.png") }
	, m_PosCoin{320.f, 412.f}
	, m_pTextFont{}
	, m_pTextFontBold{}
	, m_Lives{lives}
	, m_Level{level}
	, m_pTextX{}
	, m_pText00{}
	, m_pScore{}
	, m_pTextLevel{}
	, m_pTextTime{}
	, m_pTextMario{}
{
	m_pTextFont = TTF_OpenFont("Fonts/Inconsolata-ExtraLight.ttf", 32);
	m_pTextFontBold = TTF_OpenFont("Fonts/Inconsolata-ExtraBold.ttf", 28);
	m_pTextX = new Texture("X", m_pTextFont, Color4f{ 1,1,1,1 });
	m_pText00 = new Texture("00", m_pTextFontBold, Color4f{ 1,1,1,1 });
	m_pScore = new Texture("000000", m_pTextFontBold, Color4f{ 1,1,1,1 });
	m_pTextLevel = new Texture("LEVEL", m_pTextFontBold, Color4f{ 1,1,1,1 });
	m_pTextTime = new Texture("TIME", m_pTextFontBold, Color4f{ 1,1,1,1 });
	m_pTextMario = new Texture("MARIO", m_pTextFontBold, Color4f{ 1,1,1,1 });
}
LoadingScreen::~LoadingScreen()
{
	delete m_pTextX;
	delete m_pText00;
	delete m_pScore;
	delete m_pMarioTexture;
	delete m_pCoinTexture;
	delete m_pTextLevel;
	delete m_pTextTime;
	delete m_pTextMario;
	TTF_CloseFont(m_pTextFont);
	TTF_CloseFont(m_pTextFontBold);
}
void LoadingScreen::Draw()
{
	float sourceWidth{ m_pMarioTexture->GetWidth()};
	float sourceHeight{ m_pMarioTexture->GetHeight()};
	Rectf dst{ m_PosMario.x, m_PosMario.y,sourceWidth / 2, sourceHeight / 2 };

	float sourceWidthCoin{ m_pCoinTexture->GetWidth() };
	float sourceHeightCoin{ m_pCoinTexture->GetHeight() };
	Rectf dstCoin{ m_PosCoin.x, m_PosCoin.y, sourceWidthCoin, sourceHeightCoin};

	Rectf dstX{ 400.f, 200.f, 10.f, 25 };
	Rectf dstX2{ 340.f, 408.f, 10.f, 25 };
	Rectf dst00{ 360.f, 408.f, 28.f, 28 };
	Rectf dstScore{ 150.f, 408.f, 90.f, 28 };

	if (m_pBeginScreen->HasStartedGame())
	{
		if (m_Time >= 0.f)
		{
			
			utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
			utils::FillRect(0.f, 0.f, Window().width * 2, Window().height * 2);
			m_pMarioTexture->Draw(dst);
			m_pCoinTexture->Draw(dstCoin);
			m_pTextX->Draw(dstX);
			m_pTextX->Draw(dstX2);
			m_pText00->Draw(dst00);
			m_pScore->Draw(dstScore);
			m_pTextLevel->Draw(Point2f(360, 270));
			m_pTextLevel->Draw(Point2f(450, 430));
			m_pTextMario->Draw(Point2f(150, 430));
			m_pTextTime->Draw(Point2f(590, 430));
			TextureHelper::DrawInt((int)m_Lives, Point2f(450, 200), m_pTextFont);
			TextureHelper::DrawInt((int)m_Level, Point2f(440, 270), m_pTextFontBold);
			TextureHelper::DrawInt((int)m_Level, Point2f(478, 408), m_pTextFontBold);
		}
	}
	//HasStartedGame()
}

void LoadingScreen::Update(float elapsedSec, GameState* gameState)
{
	if (m_pBeginScreen->HasStartedGame())
	{
		m_Time -= elapsedSec;
	}
	if (m_Time <= 0.f)
	{
		LoadGame = true;
	}
	m_Lives = gameState->GetAmountOfLives();
}

bool LoadingScreen::HasLoadGame()
{
	return LoadGame;
}