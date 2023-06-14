#include "pch.h"
#include "NormalMan.h"
#include <iostream>
#include <utils.h>


// (float horSpeed, float jumpSpeed, Texture* spriteTexture, float spriteClipHeight, float spriteClipWidth, float avatarWidth, float avatarHeight)

NormalMan::NormalMan() : Avatar(NormalManType ,200.f, 600.f, "Images/mario.png", 325.f, 160.f, 12.f, 15.f, 4)
	, m_TimerIsHit{0.2f}
	, m_TimeInterval{0.1f}
{

}
NormalMan::~NormalMan()
{

}

void NormalMan::Draw(const AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 14 };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 10 };

	Rectf src{};
	Rectf dst{ avatarState->GetPositionAvatar().x - GetAvatarWidth() / 4, avatarState->GetPositionAvatar().y,sourceWidth / 8, sourceHeight / 8 };
	
	if (avatarState->GetActionState() == AvatarState::ActionState::jumping)
	{
		src = Rectf{ GetSpriteClipWidth() * 5,GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::moving)
	{
		src = Rectf{ GetSpriteClipWidth() * GetAnimFrame(),GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::waiting || avatarState->GetActionState() == AvatarState::ActionState::ducking || avatarState->GetActionState() == AvatarState::ActionState::isGoingTroughPipe)
	{
		src = Rectf{ GetSpriteClipWidth() * 0,GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::stopping)
	{
		src = Rectf{ GetSpriteClipWidth() * 4,GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::dead)
	{
		src = Rectf{ GetSpriteClipWidth() * 6,GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::grabing)
	{
		src = Rectf{ GetSpriteClipWidth() * (7 + (GetAnimFrame()%2)),GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::endLevel)
	{
		
		src = Rectf{ GetSpriteClipWidth() * GetAnimFrame(),GetSpriteClipHeight(),sourceWidth,sourceHeight };
	}
	if (avatarState->GetVelocityAvatar().x < 0.f && avatarState->GetActionState() != AvatarState::ActionState::stopping) {
		glPushMatrix();
		glTranslatef(avatarState->GetPositionAvatar().x + GetAvatarWidth()/2, avatarState->GetPositionAvatar().y + GetAvatarHeight()/2, 0);
		glScalef(-1, 1, 1);
		glTranslatef(-avatarState->GetPositionAvatar().x - GetAvatarWidth()/2, -avatarState->GetPositionAvatar().y - GetAvatarHeight()/2, 0);

		if (avatarState->GetCanBeHit() == false)
		{
			if (m_TimerIsHit <= m_TimeInterval)
			{
				GetSpriteTexture()->Draw(dst, src);
			}
		}
		else
		{
			GetSpriteTexture()->Draw(dst, src);
		}
		glPopMatrix();
	}
	else if (avatarState->GetVelocityAvatar().x > 0.f && avatarState->GetActionState() == AvatarState::ActionState::stopping) {
		glPushMatrix();
		glTranslatef(avatarState->GetPositionAvatar().x + GetAvatarWidth()/2, avatarState->GetPositionAvatar().y + GetAvatarHeight() / 2, 0);
		glScalef(-1, 1, 1);
		glTranslatef(-avatarState->GetPositionAvatar().x - GetAvatarWidth()/2, -avatarState->GetPositionAvatar().y - GetAvatarHeight() / 2, 0);

		if (avatarState->GetCanBeHit() == false)
		{
			if (m_TimerIsHit <= m_TimeInterval)
			{
				GetSpriteTexture()->Draw(dst, src);
			}
		}
		else
		{
			GetSpriteTexture()->Draw(dst, src);
		}
		glPopMatrix();
	}
	else
	{
		if (avatarState->GetCanBeHit() == false)
		{
			if (m_TimerIsHit <= m_TimeInterval)
			{
				GetSpriteTexture()->Draw(dst, src);
			}
		}
		else
		{
			GetSpriteTexture()->Draw(dst, src);
		}
	}
	//utils::DrawRect(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, GetAvatarWidth(), GetAvatarHeight());
}
void NormalMan::UpdateDraw(float elapsedSec)
{
	SetAnimTime(elapsedSec);
	int totalFramesElapsed{ int(GetAnimTime() / GetNrFramesPerSec()) };
	SetAnimFrame(totalFramesElapsed, GetNrOfFrames());
	
	m_TimerIsHit = m_TimerIsHit - elapsedSec;
	if (m_TimerIsHit <= 0)
	{
		m_TimerIsHit = 0.2f;
	}
}
