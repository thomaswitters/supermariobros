#include "pch.h"
#include "BiggerMan.h"
#include <iostream>
#include <utils.h>

BiggerMan::BiggerMan() : Avatar(BiggerManType, 200.f, 600.f, "Images/Mario2.png", 28.f, 29.7f, 12.f, 30.f, 3)
{

}

BiggerMan::~BiggerMan()
{
}

void BiggerMan::Draw(const AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 24 };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 5.5f };

	Rectf src{ };
	Rectf dst{ avatarState->GetPositionAvatar().x - GetAvatarWidth()/4.f, avatarState->GetPositionAvatar().y,sourceWidth, sourceHeight };

	if (avatarState->GetActionState() == AvatarState::ActionState::jumping)
	{
		src = Rectf{ GetSpriteClipWidth() * 12.1f,GetSpriteClipHeight() * 3.f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::moving)
	{
		src = Rectf{ GetSpriteClipWidth() * (8 + GetAnimFrame()),GetSpriteClipHeight() * 3.f,sourceWidth,sourceHeight };

	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::waiting || avatarState->GetActionState() == AvatarState::ActionState::isGoingTroughPipe)
	{
		src = Rectf{ GetSpriteClipWidth() * 7,GetSpriteClipHeight() * 3.f,sourceWidth,sourceHeight };

	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::stopping)
	{
		src = Rectf{ GetSpriteClipWidth() * 11,GetSpriteClipHeight() * 3.f,sourceWidth,sourceHeight };

	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::ducking)
	{
		src = Rectf{ GetSpriteClipWidth() * 13.1f,GetSpriteClipHeight() * 2.8f,sourceWidth,sourceHeight };

	}
	if (avatarState->GetVelocityAvatar().x < 0.f) {
		glPushMatrix();
		glTranslatef(avatarState->GetPositionAvatar().x + GetAvatarWidth()/2, avatarState->GetPositionAvatar().y + GetAvatarHeight() / 2, 0);
		glScalef(-1, 1, 1);
		glTranslatef(-avatarState->GetPositionAvatar().x - GetAvatarWidth()/2, -avatarState->GetPositionAvatar().y - GetAvatarHeight() / 2, 0);

		GetSpriteTexture()->Draw(dst, src);
		glPopMatrix();
	}
	else
	{
		GetSpriteTexture()->Draw(dst, src);
	}
	//utils::DrawRect(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, GetAvatarWidth(), GetAvatarHeight());

}
void BiggerMan::UpdateDraw(float elapsedSec)
{
	SetAnimTime(elapsedSec);
	int totalFramesElapsed{ int(GetAnimTime() / GetNrFramesPerSec()) };
	SetAnimFrame(totalFramesElapsed, GetNrOfFrames());
	
}
