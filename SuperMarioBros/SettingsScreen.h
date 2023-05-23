#pragma once
#include <Texture.h>
#include <SoundStream.h>
#include "GameState.h"

class SettingsScreen
{
public:
	SettingsScreen();
	virtual ~SettingsScreen();
	void Draw();
	void Update(float elapsedSec, GameState* gameState);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e, bool& hasOpenedSettings);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e, bool& hasOpenedSettings);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
private:
	Texture* m_pSettingsBackground;
	Texture* m_pCloseTexture;
	Texture* m_pToggleButtomTexture;
	Texture* m_pDragIconTexture;
	TTF_Font* m_pTextTitelFont;
	TTF_Font* m_pTextFont;
	Texture* m_pTextSettings;
	Texture* m_pTextSound;

	Rectf m_PosClose;
	Rectf m_PosDragIcon;
	Rectf m_PosToggleButton;
	bool m_PlayingSong;

	SoundStream* m_SoundStreamMario;

	bool m_IsDragging;
	Rectf m_PosDragButton;
	Point2f m_PosDragButtonText;

};

