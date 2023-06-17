#include "pch.h"
#include "FlowerMan.h"
#include <iostream>
#include <utils.h>


FlowerMan::FlowerMan() : Avatar(FlowerManType, 200.f, 600.f, "Images/Mario2.png", 29.f, 25.6f, 12.f, 30.f, 4)
{

}

FlowerMan::~FlowerMan()
{
}

void FlowerMan::Draw(const AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 19 };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 6.f };

	Rectf src{ };
	Rectf dst{ avatarState->GetPositionAvatar().x - GetAvatarWidth() / 2, avatarState->GetPositionAvatar().y,sourceWidth, sourceHeight };

	if (avatarState->GetActionState() == AvatarState::ActionState::jumping)
	{
		src = Rectf{ GetSpriteClipWidth() * 14,GetSpriteClipHeight() * 5.3f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::moving)
	{
		src = Rectf{ GetSpriteClipWidth() * (9 + GetAnimFrame()),GetSpriteClipHeight() * 5.3f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::waiting || avatarState->GetActionState() == AvatarState::ActionState::isGoingTroughPipe)
	{
		src = Rectf{ GetSpriteClipWidth() * 8,GetSpriteClipHeight() * 5.3f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::stopping)
	{
		src = Rectf{ GetSpriteClipWidth() * 13.f,GetSpriteClipHeight() * 5.3f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::ducking)
	{
		src = Rectf{ GetSpriteClipWidth() * 15.f,GetSpriteClipHeight() * 5.15f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::grabing)
	{
		src = Rectf{ GetSpriteClipWidth() * 14.f,GetSpriteClipHeight() * 6.4f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::endLevel)
	{
		src = Rectf{ GetSpriteClipWidth() * (9 + GetAnimFrame()),GetSpriteClipHeight() * 5.3f,sourceWidth,sourceHeight };
	}
	else if (avatarState->GetActionState() == AvatarState::ActionState::respawning)
	{
		src = Rectf{ GetSpriteClipWidth() * 8,GetSpriteClipHeight() * 5.3f,sourceWidth,sourceHeight };
	}
	if (avatarState->GetVelocityAvatar().x < 0.f /*&& avatarState->GetActionState() != AvatarState::ActionState::stopping*/) {
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
	//utils::SetColor(Color4f(1.0f, 0.f, 0.f, 1.f));
	//utils::DrawRect(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, GetAvatarWidth(), GetAvatarHeight());
	//utils::DrawRect(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, GetAvatarWidth(), GetAvatarHeight());
}
void FlowerMan::UpdateDraw(float elapsedSec)
{
	SetAnimTime(elapsedSec);
	int totalFramesElapsed{ int(GetAnimTime() / GetNrFramesPerSec()) };
	SetAnimFrame(totalFramesElapsed, GetNrOfFrames());
}
