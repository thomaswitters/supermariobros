#include "pch.h"
#include "SettingsScreen.h"
#include <utils.h>
#include <iostream>
#include "Hud.h"

SettingsScreen::SettingsScreen()
	: m_pSettingsBackground{new Texture("Images/SettingsBackground.png")}
	, m_pCloseTexture{new Texture("Images/close.png")}
	, m_pToggleButtomTexture{new Texture("Images/OnOffButton4.png")}
	, m_pDragIconTexture{new Texture("Images/dragIcon.png")}
	, m_pTextTitelFont{}
	, m_pTextFont{}
	, m_pTextSettings{}
	, m_pTextSound{}
	, m_PosClose{ 565.f, 375.f, 40.f, 40.f }
	, m_PosToggleButton{328.f, 318.f, m_pToggleButtomTexture->GetWidth(), m_pToggleButtomTexture->GetHeight()}
	, m_PosDragIcon{330.f, 243.f, m_pDragIconTexture->GetWidth(), m_pDragIconTexture->GetHeight() / 2 }
	, m_PlayingSong{false}
	, m_SoundStreamMario{ new SoundStream("Sounds/Mario.mp3") }
	, m_IsDragging{false}
	, m_PosDragButton{ 585.f, 259.f, 20.f, 20.f }
	, m_PosDragButtonText{ m_PosDragButton.left - m_PosDragButton.width / 1.3f, m_PosDragButton.bottom - m_PosDragButton.height / 2 }

{
	m_pTextTitelFont = TTF_OpenFont("Fonts/Inconsolata-ExtraBold.ttf", 28);
	m_pTextFont = TTF_OpenFont("Fonts/Inconsolata-ExtraBold.ttf", 20);
	m_pTextSettings = new Texture("SETTINGS", m_pTextTitelFont, Color4f{ 1,1,1,1 });
	m_pTextSound = new Texture("MUSIC", m_pTextFont, Color4f{ 1,1,1,1 });
}
SettingsScreen::~SettingsScreen()
{
	delete m_pDragIconTexture;
	delete m_SoundStreamMario;
	delete m_pSettingsBackground;
	delete m_pCloseTexture;
	delete m_pTextSettings;
	delete m_pTextSound;
	delete m_pToggleButtomTexture;
	TTF_CloseFont(m_pTextTitelFont);
	TTF_CloseFont(m_pTextFont);
}
void SettingsScreen::Draw()
{
	/*float sourceWidth{ m_pSettingsBackground->GetWidth() / 2.f };
	float sourceHeight{ m_pSettingsBackground->GetHeight() / 2.f };
	Rectf dst{ 0.f, 0.f,sourceWidth, sourceHeight };
	m_pSettingsBackground->Draw(dst);*/

	utils::SetColor(Color4f(0.1f, 0.7f, 0.4f, 0.8f));
	utils::FillRect(Rectf(210.f, 70.f, 400.f, 350.f));

	utils::SetColor(Color4f(0.1f, 0.5, 0.4f, 0.9f));
	utils::FillRect(Rectf(210.f, 370.f, 400.f, 50.f));

	utils::SetColor(Color4f(0.1f, 0.5, 0.4f, 1.f));
	utils::DrawLine(240.f, 300.f, 580.f, 300.f);

	utils::SetColor(Color4f(0.1f, 0.5, 0.4f, 1.f));
	utils::DrawLine(240.f, 220.f, 580.f, 220.f);

	utils::SetColor(Color4f(0.1f, 0.5, 0.4f, 1.f));
	utils::DrawLine(240.f, 140.f, 580.f, 140.f);

	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.f));
	utils::DrawRect(Rectf(210.f, 70.f, 400.f, 350.f));

	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::DrawLine(210.f, 370.f, 610.f, 370.f);

	m_pTextSettings->Draw(Point2f(360.f, 380.f));

	m_pTextSound->Draw(Point2f(250.f, 325.f));
	m_pTextSound->Draw(Point2f(250.f, 250.f));
	/*utils::SetColor(Color4f(0.1f, 0.5, 0.4f, 0.9f));
	utils::FillRect(Rectf(340.f, 325.f, 50.f, 20.f));*/

	m_pCloseTexture->Draw(m_PosClose);

	if (m_PlayingSong)
	{
		float sourceWidth{ m_PosToggleButton.width };
		float sourceHeight{ m_PosToggleButton.height / 2 };
		Rectf src{ 0.f, 0.f,sourceWidth, sourceHeight };
		Rectf dst{ m_PosToggleButton.left, m_PosToggleButton.bottom,sourceWidth, sourceHeight};
		m_pToggleButtomTexture->Draw(dst, src);

		//float sourceWidthDrag{ m_pDragIconTexture->GetWidth()};
		//float sourceHeightDrag{ m_pDragIconTexture->GetHeight()/2};
		Rectf srcDrag{ 0.f, 0.f,m_PosDragIcon.width, m_PosDragIcon.height };
		Rectf dstDrag{ m_PosDragIcon.left, m_PosDragIcon.bottom,m_PosDragIcon.width, m_PosDragIcon.height};
		m_pDragIconTexture->Draw(dstDrag, srcDrag);
	}
	else if (!m_PlayingSong)
	{
		float sourceWidth{ m_PosToggleButton.width};
		float sourceHeight{ m_PosToggleButton.height / 2 };
		Rectf src{ 0.f, 35.f,sourceWidth, sourceHeight };
		Rectf dst{ m_PosToggleButton.left, m_PosToggleButton.bottom,sourceWidth, sourceHeight};
		m_pToggleButtomTexture->Draw(dst, src);

		Rectf srcDrag{ 0.f, 36.f, m_PosDragIcon.width, m_PosDragIcon.height };
		Rectf dstDrag{ m_PosDragIcon.left, m_PosDragIcon.bottom,m_PosDragIcon.width, m_PosDragIcon.height };
		m_pDragIconTexture->Draw(dstDrag, srcDrag);
	}

	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::FillEllipse(m_PosDragButton.left, m_PosDragButton.bottom, m_PosDragButton.width, m_PosDragButton.height);


	if (m_SoundStreamMario->GetVolume() >= 100)
	{
		m_PosDragButtonText = Point2f(m_PosDragButton.left - m_PosDragButton.width / 1.3f, m_PosDragButton.bottom - m_PosDragButton.height / 2.f);		
	}
	else if(m_SoundStreamMario->GetVolume() < 10)
	{
		m_PosDragButtonText = Point2f(m_PosDragButton.left - m_PosDragButton.width / 4.f, m_PosDragButton.bottom - m_PosDragButton.height / 2.f);
	}
	else
	{
		m_PosDragButtonText = Point2f(m_PosDragButton.left - m_PosDragButton.width / 2.f, m_PosDragButton.bottom - m_PosDragButton.height / 2.f);
	}
	TextureHelper::DrawInt(m_SoundStreamMario->GetVolume(), m_PosDragButtonText, m_pTextFont);
}

void SettingsScreen::Update(float elapsedSec, GameState* gameState)
{

}

void SettingsScreen::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e, bool& hasOpenedSettings, GameState* gameState)
{
	float sourceWidth{ m_PosToggleButton.width };
	float sourceHeight{ m_PosToggleButton.height / 2 };
	Rectf dst{ m_PosToggleButton.left, m_PosToggleButton.bottom,sourceWidth / 1.f, sourceHeight / 1.f };

	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
			if (e.x >= m_PosClose.left && e.y >= m_PosClose.bottom && e.x <= m_PosClose.left + m_PosClose.width && e.y <= m_PosClose.bottom + m_PosClose.height)
			{
				hasOpenedSettings = false;
				
			}
			//else if (e.x >= m_PosDragIcon.left && e.y >= m_PosDragIcon.bottom && e.x <= m_PosDragIcon.left + m_PosDragIcon.width && e.y <= m_PosDragIcon.bottom + m_PosDragIcon.height)
			//{
			//	m_IsDragging = false;
			//	//std::cout <<  << std::endl;
			//}
			else if (m_IsDragging)
			{
				m_IsDragging = false;
				
			}
			else if (e.x >= dst.left && e.y >= dst.bottom && e.x <= dst.left + dst.width && e.y <= dst.bottom + dst.height)
			{
				m_PlayingSong = !m_PlayingSong;
				
				if (m_PlayingSong)
				{
					
					m_SoundStreamMario->Play(true);
					
				}
				else
				{
					m_SoundStreamMario->Stop();
				}
			}
		break;
		
	}
}

void SettingsScreen::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e, bool& hasOpenedSettings)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		
		if (e.x >= m_PosDragButton.left - m_PosDragButton.width && e.y >= m_PosDragButton.bottom - m_PosDragButton.height && e.x <= m_PosDragButton.left + m_PosDragButton.width && e.y <= m_PosDragButton.bottom + m_PosDragButton.height)
		{
			
			m_IsDragging = true;
		}
		else if (e.x >= m_PosDragIcon.left && e.y >= m_PosDragIcon.bottom && e.x <= m_PosDragIcon.left + m_PosDragIcon.width && e.y <= m_PosDragIcon.bottom + m_PosDragIcon.height)
		{
			m_PosDragButton.left = float(e.x);
			float posInsideDragIcon;
			float percentInsideDragIcon;
			posInsideDragIcon = e.x - m_PosDragIcon.left;
			percentInsideDragIcon = posInsideDragIcon / m_PosDragIcon.width * 128;

			m_SoundStreamMario->SetVolume(int(percentInsideDragIcon));
			m_IsDragging = false;
		}
		else
		{
			m_IsDragging = false;
		}
	}
}
void SettingsScreen::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//if (m_IsDragging && e.x >= m_PosDragIcon.left && e.y >= m_PosDragIcon.bottom && e.x <= m_PosDragIcon.left + m_PosDragIcon.width && e.y <= m_PosDragIcon.bottom + m_PosDragIcon.height)
	//{
		
	//}
	if (m_IsDragging)
	{
		m_PosDragButton.left = float(e.x);

		if (m_PosDragButton.left <= m_PosDragIcon.left)
		{
			m_PosDragButton.left = m_PosDragIcon.left;
		}
		else if (m_PosDragButton.left >= m_PosDragIcon.left + m_PosDragIcon.width)
		{
			m_PosDragButton.left = m_PosDragIcon.left + m_PosDragIcon.width;
		}
		
		float posInsideDragIcon;
		float percentInsideDragIcon;
		posInsideDragIcon = e.x - m_PosDragIcon.left;
		percentInsideDragIcon = posInsideDragIcon / m_PosDragIcon.width * 128;

		m_SoundStreamMario->SetVolume(int(percentInsideDragIcon));

	}
}
