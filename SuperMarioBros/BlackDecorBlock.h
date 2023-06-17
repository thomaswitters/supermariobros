#pragma once
#include "GameItem.h"

class BlackDecorBlock : public GameItem
{
public:
	BlackDecorBlock(Point2f GameItemPos);
	virtual ~BlackDecorBlock();
	void Draw(AvatarState* avatarState) const;
	virtual bool CanCollide(GameItem* gameItem) {
		return false;
	}
private:
	Point2f m_Pos;
};