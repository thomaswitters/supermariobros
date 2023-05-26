#pragma once
#include "GameItem.h"

class QuestionBlock : public GameItem
{
public:
	QuestionBlock(Point2f GameItemPos);
	virtual ~QuestionBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
protected:
	bool GetIsHitFlower() const
	{
		return m_IsHitFlower;
	}
	bool GetIsHitMushRoom() const
	{
		return m_IsHitMushRoom;
	}

private:
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	float m_BeginPosY;
	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
	float m_Counter;

	bool m_IsHitFlower;
	bool m_IsHitMushRoom;
};

