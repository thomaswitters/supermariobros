#include "pch.h"
#include "AvatarState.h"

AvatarState::AvatarState(Avatar *initialAvatar)
	: m_AvatarX{ 100.f }
	, m_AvatarY{ 400.f }
	, m_Velocity{ 0.f, 0.f }
	, m_Acceleration{ 0.f, -981.f }
	, m_currentAvatar{ initialAvatar }
	, m_CountStartJump{0.40f}
	, m_JumpTime{}
	, m_IsJumping{false}
{

}
AvatarState::~AvatarState() {

}
Point2f AvatarState::GetPositionAvatar() const
{
	return Point2f(m_AvatarX, m_AvatarY);
}
void AvatarState::SetPositionVelosityAvatar(Vector2f m_Velocity, float elapsedSec)
{
	m_AvatarX += m_Velocity.x * elapsedSec;
	m_AvatarY += m_Velocity.y * elapsedSec;	
}
void AvatarState::SetPositionYAvatar(float y)
{
	m_AvatarY = y;
}
void AvatarState::SetPositionXCollisionLeftAvatar(float x, float width)
{
	m_AvatarX = x - width;
}
void AvatarState::SetPositionXCollisionRightAvatar(float x, float width)
{
	m_AvatarX = x + width;
}
void AvatarState::SetPositionYCollisionBottomAvatar(float y, float height)
{
	m_AvatarY = y - height;
}
void AvatarState::SetPositionYCollisionTopAvatar(float y, float height)
{
	m_AvatarY = y + height;
}
void AvatarState::SetVelocityXCollisionAvatar(float x)
{
	m_Velocity.x = x;
}
void AvatarState::SetVelocityYCollisionBottomAvatar()
{
	m_Velocity.y = 1.f;
}
void AvatarState::SetVelocityYCollisionTopAvatar()
{
	m_Velocity.y = 0.f;
}

Vector2f AvatarState::GetVelocityAvatar() const
{
	return m_Velocity;
}

void AvatarState::SetVelocityAvatar(Vector2f m_Acceleration, float elapsedSec)
{
	m_Velocity += m_Acceleration * elapsedSec;
}
void AvatarState::SetVelocityPosXAvatar(float x)
{
	if (m_Velocity.x <= 80.f && m_Velocity.x >= -80.f)
	{
		m_Velocity.x += x;
	}
	else if (m_Velocity.x >= 80.f && m_Velocity.x <= 180.f)
	{
		m_Velocity.x += x - 2;
	}
	else if (m_Velocity.x <= -80.f && m_Velocity.x >= -180.f)
	{
		m_Velocity.x += x + 2;
	}
	else if (m_Velocity.x >= 180.f)
	{
		m_Velocity.x = 180.f;
	}
	else if (m_Velocity.x <= -180.f)
	{
		m_Velocity.x = -180.f;
	}
	//std::cout << m_Velocity.x << std::endl;
}
void AvatarState::SetVelocityJumpAvatar(float y)
{
	m_Velocity.y = float(sqrt(2.0f * 981.f * y));
	//m_CountStartJump++;
}
void AvatarState::SetVelocityYAvatar(float y)
{
	m_Velocity.y = y;
}

Vector2f AvatarState::GetAccelerationAvatar()
{
	return m_Acceleration;
}

void AvatarState::SetCurrentAvatar(Avatar* currentAvatar) {
	m_currentAvatar = currentAvatar;
}
Avatar* AvatarState::GetCurrentAvatar() const {
	return m_currentAvatar;
}
void AvatarState::ResetAvatar(Avatar* normalMan) {
	m_currentAvatar = normalMan;
}

AvatarState::ActionState AvatarState::GetActionState() const
{
	return m_ActionState;
}
void AvatarState::SetActionState(ActionState actionState)
{
	m_ActionState = actionState;
}

//void AvatarState::UpdateAvatarState()
//{
//	if (m_Velocity.y <= 0.f && m_Velocity.x < 0.f && m_Velocity.x > 0.f)
//	{
//		m_ActionState = ActionState::moving;
//	}
//	else if (m_Velocity.y > 0.f)
//	{
//		m_ActionState = ActionState::jumping;
//	}
//}


void AvatarState::Update(float elapsedSec, AvatarState* avatarState, Level* level, Point2f cameraPos)
{
	HandleKeys(elapsedSec);

	SetVelocityAvatar(m_Acceleration, elapsedSec);
	SetPositionVelosityAvatar(m_Velocity, elapsedSec);
	
	if (level->IsOnGround(avatarState))
	{
		m_IsOnGround = true;
	}
	else
	{
		m_IsOnGround = false;
	}

	if (m_ActionState == AvatarState::ActionState::moving)
	{
		if (!CheckKeys() && m_IsOnGround && m_Velocity.x <= 20.f && m_Velocity.x >= -20.f)
		{
			SetActionState(AvatarState::ActionState::waiting);
		}
		else if (m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::moving);
		}
		else if (!m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::jumping);

		}
	}
	if (m_ActionState == AvatarState::ActionState::jumping)
	{
		
		if (!CheckKeys() && m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::waiting);
		}
		else if (m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::moving);
		}
		else if (!m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::jumping);
			
		}
	}
	if (m_ActionState == AvatarState::ActionState::stopping)
	{
		if (!CheckKeys() && m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::waiting);
		}
	}
	if (m_ActionState == AvatarState::ActionState::ducking)
	{
		if (!CheckKeys() && m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::waiting);
		}
		else if (!CheckKeyDown())
		{
			SetActionState(AvatarState::ActionState::jumping);
		}
		else
		{
			SetActionState(AvatarState::ActionState::ducking);
		}
	}
	UpdatePosition(elapsedSec, cameraPos);
}
void AvatarState::UpdatePosition(float elapsedSec, Point2f cameraPos)
{
	if (m_AvatarX <= 0.f)
	{
		m_AvatarX = 0.f;
		m_Velocity.x = -1;
	}

	if (m_Velocity.x <= 0.f)
	{
		if (m_AvatarX <= cameraPos.x - Window().width / 2 + 20.f)
		{
			m_AvatarX = cameraPos.x - Window().width / 2 + 20.f;
			m_Velocity.x = -1;
		}
	}
	
	
}

void AvatarState::HandleKeys(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (m_ActionState != ActionState::ducking)
	{
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			SetVelocityPosXAvatar(2.5f);
			SetActionState(AvatarState::ActionState::moving);


			if (m_IsOnGround)
			{
				m_ActionState = ActionState::moving;
			}

			if (m_Velocity.x <= 0.f && m_IsOnGround)
			{
				m_ActionState = ActionState::stopping;
			}

		}
		else if (pStates[SDL_SCANCODE_LEFT])
		{
			SetVelocityPosXAvatar(-2.5f);
			SetActionState(AvatarState::ActionState::moving);
			if (m_Velocity.x >= 0.f && m_IsOnGround)
			{
				m_ActionState = ActionState::stopping;
			}
		}
		else
		{
			m_Velocity.x *= 0.96f;
		}
	}
	
	
	if (pStates[SDL_SCANCODE_UP])
	{

		if (m_IsOnGround)
		{
			m_IsJumping = true;
			m_JumpTime = m_CountStartJump;
			
			
			SetVelocityJumpAvatar(20.f);

			SetActionState(AvatarState::ActionState::jumping);
			//m_CountJump = 0.f;
		}

	}
	if (pStates[SDL_SCANCODE_UP] && m_IsJumping == true)
	{
		if (m_JumpTime > 0.f)
		{
			
			m_JumpTime -= elapsedSec;
			SetVelocityJumpAvatar(20.f);
			//std::cout << m_JumpTime << std::endl;
		}
		else
		{
			m_IsJumping = false;
		}
	}
	else
	{
		m_IsJumping = false;
	}

	if (pStates[SDL_SCANCODE_DOWN])
	{
		m_ActionState = ActionState::ducking;
		if (m_IsOnGround)
		{
			m_Velocity.x *= 0.96f;
		}
	} 
	if (pStates[SDL_SCANCODE_SPACE])
	{
		if (GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			if (m_ActionState != ActionState::ducking)
			{
				std::cout << "shoot";
			}
			
		}
	}

	
	//else if (pStates[SDL_SCANCODE_DOWN] && pStates[SDL_SCANCODE_UP])
	//{
	//	m_ActionState = ActionState::ducking;
	//	//m_Velocity.x *= 0.96f;
	//}
	
	
	
	
}
bool AvatarState::CheckKeys()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
		return true;
	if (pStates[SDL_SCANCODE_LEFT])
		return true;
	if (pStates[SDL_SCANCODE_UP])
		return true;
	if (pStates[SDL_SCANCODE_DOWN])
		return true;
	return false;

}
bool AvatarState::CheckKeyDown()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_DOWN])
		return true;
	return false;
}



