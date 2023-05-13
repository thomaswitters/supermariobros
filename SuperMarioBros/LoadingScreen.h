#pragma once
#include "BeginVieuw.h"
#include "Hud.h"
class TextureHelper;
class LoadingScreen
{
public:
	LoadingScreen(BeginVieuw* beginScreen, int level, int lives);
	virtual ~LoadingScreen();
	void Draw();
	void Update(float elapsedSec, GameState* gameState);
	bool HasLoadGame();
private:
	BeginVieuw* m_pBeginScreen;
	float m_Time;
	bool LoadGame;
	Texture* m_pMarioTexture;
	Point2f m_PosMario;
	Texture* m_pCoinTexture;
	Point2f m_PosCoin;

	TTF_Font* m_pTextFont;
	TTF_Font* m_pTextFontBold;
	Texture* m_pTextX;
	Texture* m_pText00;
	Texture* m_pScore;
	Texture* m_pTextLevel;
	Texture* m_pTextTime;
	Texture* m_pTextMario;
	int m_Lives;
	int m_Level;
};

