#pragma once
#include "GameItem.h"

class BlueDecorBlock : public GameItem
{
public:
	BlueDecorBlock(Point2f GameItemPos);
	virtual ~BlueDecorBlock();
	void Draw(AvatarState* avatarState) const;
	virtual bool CanCollide(GameItem* gameItem) {
		return false;
	}
private:
	Point2f m_Pos;
};

