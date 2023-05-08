#include "pch.h"
#include "BeginVieuw.h"
#include <utils.h>
#include <iostream>

BeginVieuw::BeginVieuw()
	: m_pBeginBackground{new Texture("Images/StartScreen3.png")}
	, m_pMiniMushroom{ new Texture("Images/StartScreen2.png") }
	, HasStarted{false}
	, m_pTextFont{}
	, m_pText1Player{}
	, m_pText2Player{}
	, MushroomPos{ Point2f(285.f, 175.f) }
{
	m_pTextFont = TTF_OpenFont("Fonts/Inconsolata-Black.ttf", 60);
	m_pText1Player = new Texture("1 PLAYER GAME", m_pTextFont, Color4f{ 1,1,1,1 });
	m_pText2Player = new Texture("2 PLAYER GAME", m_pTextFont, Color4f{ 1,1,1,1 });
}
BeginVieuw::~BeginVieuw()
{
	delete m_pBeginBackground;
	delete m_pMiniMushroom;
	delete m_pText1Player;
	delete m_pText2Player;
	TTF_CloseFont(m_pTextFont);
}

void BeginVieuw::Draw()
{
	float sourceWidth{ m_pBeginBackground->GetWidth()*2.5f};
	float sourceHeight{ m_pBeginBackground->GetHeight()*2.2f};

	Rectf dst{100.f, 0.f,sourceWidth, sourceHeight };
	m_pBeginBackground->Draw(dst);
	
	//background text
	utils::SetColor(Color4f(0.41f, 0.53f, 0.98f, 1.0f));
	utils::FillRect(Rectf(320.f, 140.f, 260.f, 20.f));
	utils::SetColor(Color4f(0.41f, 0.53f, 0.98f, 1.0f));
	utils::FillRect(Rectf(280.f, 175.f, 300.f, 20.f));

	float sourceWidthMushroom{ m_pMiniMushroom->GetWidth() * 2.0f };
	float sourceHeightMushroom{ m_pMiniMushroom->GetHeight() * 2.0f };
	Rectf dstMushroom{ MushroomPos.x, MushroomPos.y,sourceWidthMushroom, sourceHeightMushroom };
	m_pMiniMushroom->Draw(dstMushroom);

	//text
	Rectf dst1Player{ 320.f, 175.f, 260.f, 25 };
	Rectf dst2Player{ 320.f, 140.f, 260.f, 25 };
	m_pText1Player->Draw(dst1Player);
	m_pText2Player->Draw(dst2Player);
}

void BeginVieuw::Update(float elapsedSec)
{
	
}
void BeginVieuw::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	if (!HasStarted)
	{
		//std::cout << "  [" << e.x << ", " << e.y << "]\n";
		if (e.x >= 320.f && e.y >= 140.f && e.x <= 580.f && e.y <= 165.f)
		{
			MushroomPos = Point2f(285.f, 140.f);
		}
		else if (e.x >= 320.f && e.y >= 175.f && e.x <= 580.f && e.y <= 200.f)
		{
			MushroomPos = Point2f(285.f, 175.f);
		}
	}
}
void BeginVieuw::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (!HasStarted)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
			if (e.x >= 320.f && e.y >= 175.f && e.x <= 580.f && e.y <= 200.f)
			{
				HasStarted = true;
				std::cout << " started player1" << std::endl;
			}
			break;
		}
	}
	
}

bool BeginVieuw::HasStartedGame()
{
	return HasStarted;
}