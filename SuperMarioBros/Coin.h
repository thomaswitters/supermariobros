#pragma once
#include "GameItem.h"

class Coin : public GameItem
{
public:
	Coin(Point2f GameItemPos);
	virtual ~Coin();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Point2f m_PosCoin;

	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	bool m_IsHit;
	float m_Teller;

};

