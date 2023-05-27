#pragma once
#include "Pipe.h"

enum HorizonDirection { FromLeftToRight, FromRightToLeft };
class HorizontalPipe : public Pipe {
public:
	/*
	 * transportToPos will be deleted by HorizontalPipe
	 */
	HorizontalPipe(HorizonDirection horizonDirection, Point2f GameItemPos, float width, Point2f* transportToPos);
	virtual ~HorizontalPipe();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	
private:
	HorizonDirection m_HorizonDirection;
};

