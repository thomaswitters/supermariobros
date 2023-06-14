#pragma once
#include "GameItem.h"

class Pipe : public GameItem
{
public:
	/*
	 * transportToPos will be deleted by Pipe
	 */
	Pipe(Point2f GameItemPos, float spriteClipHeight, float spriteClipWidth, float GameItemWidth, float GameItemHeight, Point2f* transportToPos, const std::string& soundPath);
	virtual ~Pipe();

	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);

private:
	Texture* m_pSpriteTextureBottom;
	Point2f* m_transportToPos;

protected:
	Texture* GetSpriteTextureBottom() const {
		return m_pSpriteTextureBottom;
	}
	Point2f* GetTransportToPos() {
		return m_transportToPos;
	}
};
