#pragma once
#include "GameItem.h"

class CoinPickUp : public GameItem
{
public:
	CoinPickUp(Point2f GameItemPos);
	virtual ~CoinPickUp();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Point2f m_PosCoin;
	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
};