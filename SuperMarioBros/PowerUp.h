#pragma once
#include "GameItem.h"

class PowerUp : public GameItem
{
public:
	PowerUp(Point2f GameItemPos);
	virtual ~PowerUp();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Point2f m_PosPowerUp;
	float m_Teller;

	bool m_IsHitFlower;
	bool m_IsHitMushRoom;
	bool m_CanPickUpFlower;
	bool m_CanPickUpMushRoom;

	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	Vector2f m_Velocity;
	Vector2f m_Acceleration;
};

