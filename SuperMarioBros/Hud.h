#pragma once
#include <Texture.h>
#include "GameState.h"
#include "SettingsScreen.h"

class Hud
{
public:
	Hud(const Point2f& topLeft, float totalTime, int level, int lives, int coins, int score);
	~Hud();
	void Draw();
	void Update(float elapsedSec, GameState* gameState);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	Point2f m_BottomLeft;
	float m_TotalTime;
	int m_Level;
	int m_Lives;
	int m_Coins;
	int m_Score;
	TTF_Font* m_pTextFont;
	TTF_Font* m_pHudFont;
	//	Texture* m_pTextTimeCount;
	Texture* m_pCoins;
	Texture* m_pTextX;
	Texture* m_pTextTime;
	Texture* m_pTextLevel;
	Texture* m_pTextLives;
	Texture* m_pTextMario;
	Texture* m_pCoinTexture;
	Point2f m_PosCoin;

	Texture* m_pSettingsTexture;
	SettingsScreen* m_pSettingsScreen;
	bool m_HasOpenSettings;
};

class TextureHelper {
public:
	static void DrawInt(int IntValue, Point2f position, TTF_Font* pFont) {
		std::string str1 = std::to_string(IntValue);
		Texture* xTexture = new Texture(str1, pFont, Color4f{ 1,1,1,1 });
		xTexture->Draw(position);
		delete xTexture;
	}
};