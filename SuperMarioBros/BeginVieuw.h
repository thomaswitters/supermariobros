#pragma once
#include <Texture.h>
class BeginVieuw
{
public:
	BeginVieuw();
	~BeginVieuw();
	void Draw();
	void Update(float elapsedSec);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
	bool HasStartedGame();
private:
	Texture* m_pBeginBackground;
	Texture* m_pMiniMushroom;
	//std::string m_Text1Player;
	Texture* m_pText1Player;
	Texture* m_pText2Player;
	TTF_Font* m_pTextFont;
	bool HasStarted;
	Point2f MushroomPos;
};

