#pragma once
#include <Texture.h>

class SettingsScreen
{
public:
	SettingsScreen();
	virtual ~SettingsScreen();
	void Draw();
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
private:
	Texture* m_pSettingsBackground;
};

