#pragma once

#include "GameState.h"
#include <Vector2f.h>
#include <iostream>
#include <Texture.h>

class AvatarState;

enum AvatarType {
	NormalManType, FlowerManType, BiggerManType
};

// Characteristics of the current Avatar
class Avatar
{
public:
	Avatar(AvatarType type, float horSpeed, float jumpSpeed, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, float avatarWidth, float avatarHeight, int nrOfFrames);
	virtual ~Avatar();
	virtual void Draw(const AvatarState* avatarState) const = 0;
	virtual void UpdateDraw(float elapsedSec);

	float GetAvatarWidth() const {
		return m_AvatarWidth;
	}

	float GetAvatarHeight() const {
		return m_AvatarHeight;
	}
	AvatarType getAvatarType() const {
		return m_Type;
	}
	void SetAvatarHeight(float height)
	{
		m_AvatarHeight = height;
	}
	
protected:
	float getHorSpeed() const{
		return m_HorSpeed;
	}
	float GetJumpSpeed() const{
		return m_JumpSpeed;
	}
	Texture* GetSpriteTexture() const{
		return m_pSpriteTexture;
	}
	float GetSpriteClipHeight() const{
		return m_SpriteClipHeight;
	}
	float GetSpriteClipWidth() const{
		return m_SpriteClipWidth;
	}
	int GetNrOfFrames() const {
		return m_NrOfFrames;
	}
	float GetNrFramesPerSec() const {
		return m_NrFramesPerSec;
	}
	float GetAnimTime() const {
		return m_AnimTime;
	}
	int GetAnimFrame() const{
		return m_AnimFrame;
	}
	void SetAnimTime(float elapsedSec) {
		m_AnimTime += elapsedSec;
	}
	void SetAnimFrame(int totalFramesElapsed, int NrOfFrames) {
		m_AnimFrame = totalFramesElapsed % NrOfFrames;
	}
	void SetAvatarHeightSprite(float height)
	{
		m_SpriteClipHeight = height;
	}

private:
	AvatarType m_Type;
	float m_HorSpeed;
	float m_JumpSpeed;
	Texture* m_pSpriteTexture;
	float m_SpriteClipHeight;
	float m_SpriteClipWidth;
	float m_AvatarWidth;
	float m_AvatarHeight;
	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
};

