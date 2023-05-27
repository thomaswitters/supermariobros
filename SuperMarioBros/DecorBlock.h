#pragma once
#include "GameItem.h"

class DecorBlock : public GameItem
{
public:
	DecorBlock(Point2f GameItemPos);
	virtual ~DecorBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);

	virtual bool CanCollide(GameItem *gameItem) {
		return false; 
	}
private:
	bool m_IsHit;
	Point2f m_BeginPosSquar1;
	Point2f m_BeginPosSquar2;
	Point2f m_BeginPosSquar3;
	Point2f m_BeginPosSquar4;
	Vector2f m_Velocity1;
	Vector2f m_Velocity2;
	Vector2f m_Velocity3;
	Vector2f m_Velocity4;
	Vector2f m_Acceleration1;
	Vector2f m_Acceleration2;
	Vector2f m_Acceleration3;
	Vector2f m_Acceleration4;

	int m_CountHit;
};

