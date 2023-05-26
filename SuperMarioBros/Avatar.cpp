#include "pch.h"
#include "Avatar.h"
#include <iostream>
#include <utils.h>


Avatar::Avatar(AvatarType type, float horSpeed, float jumpSpeed, const  std::string& imagePath, float spriteClipHeight, float spriteClipWidth, float avatarWidth, float avatarHeight, int nrOfFrames)
	: m_HorSpeed{ horSpeed }
	, m_JumpSpeed{ jumpSpeed }
	, m_pSpriteTexture{ new Texture(imagePath) }
	, m_SpriteClipHeight{ spriteClipHeight }
	, m_SpriteClipWidth{ spriteClipWidth }
	, m_AvatarWidth{ avatarWidth }
	, m_AvatarHeight{ avatarHeight }
	, m_NrOfFrames{ nrOfFrames }
	, m_NrFramesPerSec{0.1f}
	, m_AnimTime{}
	, m_AnimFrame{}
	, m_Type{ type }
	
{

}

Avatar::~Avatar()
{
	if (m_pSpriteTexture) {
		delete m_pSpriteTexture;
		m_pSpriteTexture = NULL;
	}
}

void Avatar::UpdateDraw(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
	m_AnimFrame = totalFramesElapsed % m_NrOfFrames;
}

