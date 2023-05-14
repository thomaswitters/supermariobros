#include "pch.h"
#include "SettingsScreen.h"

SettingsScreen::SettingsScreen()
	: m_pSettingsBackground{new Texture("Images/SettingsBackground.png")}
{

}
SettingsScreen::~SettingsScreen()
{
	delete m_pSettingsBackground;
}
void SettingsScreen::Draw()
{
	float sourceWidth{ m_pSettingsBackground->GetWidth() / 2.f };
	float sourceHeight{ m_pSettingsBackground->GetHeight() / 2.f };
	Rectf dst{ 0.f, 0.f,sourceWidth, sourceHeight };
	m_pSettingsBackground->Draw(dst);
}
void SettingsScreen::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (e.x >=  0.f && e.y >=  0.f && e.x <=  500.f && e.y <= 500.f)
		{
		}
		break;
	}
}