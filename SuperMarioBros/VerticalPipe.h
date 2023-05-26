#pragma once
#include "Pipe.h"

enum VerticalDirection { FromTopToBottom, FromBottomToTop };
class VerticalPipe : public Pipe {
public:
	/*
	 * transportToPos will be deleted by VerticalPipe
	 */
	VerticalPipe(VerticalDirection verticalDirection, Point2f GameItemPos, float height, Point2f* transportToPos = NULL);
	virtual ~VerticalPipe();

	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
private:
	VerticalDirection m_VerticalDirection;
};
