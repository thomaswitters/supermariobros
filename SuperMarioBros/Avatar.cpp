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

	Rectf src{ };
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
