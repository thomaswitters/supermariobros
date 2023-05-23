#include "pch.h"
#include "AvatarState.h"

AvatarState::AvatarState(Avatar *initialAvatar)
	: m_AvatarX{ 120.f }
	, m_AvatarY{ 400.f }
	, m_Velocity{ 0.f, 0.f }
	, m_Acceleration{ 0.f, -981.f }
	, m_pCurrentAvatar{ initialAvatar }
	, m_CountStartJump{0.35f}
	, m_JumpTime{}
	, m_IsJumping{false}
	, m_AmmoCounterAmound{1}
	, m_RealoadingCounter{0.6f}
	, m_CanBeHit{true}
	, m_TimeToHitAgain{ 2.0f }
	, m_TimerCanBeHit{ m_TimeToHitAgain }
	, m_TimerGoingInPipe{2}
	, m_SoundEffectMarioJump{ new SoundEffect("Sounds/MarioJump.mp3") }
	
{

}
AvatarState::~AvatarState() {
	delete m_SoundEffectMarioJump;
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
	m_pCurrentAvatar = currentAvatar;
}
Avatar* AvatarState::GetCurrentAvatar() const {
	return m_pCurrentAvatar;
}
void AvatarState::ResetAvatar(Avatar* normalMan) {
	m_pCurrentAvatar = normalMan;
	m_CanBeHit = false;
}


AvatarState::ActionState AvatarState::GetActionState() const
{
	return m_ActionState;
}
void AvatarState::SetActionState(ActionState actionState)
{
	m_ActionState = actionState;

	//if (actionState == AvatarState::ActionState::isGoingTroughPipe) {
	//	SetVelocityYAvatar(-10.f);
	//	SetVelocityXCollisionAvatar(0.f);
	//}
}


void AvatarState::Update(float elapsedSec, AvatarState* avatarState, Level* level, Point2f cameraPos)
{

	if (m_ActionState != AvatarState::ActionState::dead && m_ActionState != AvatarState::ActionState::isGoingTroughPipe)
	{
		HandleKeys(elapsedSec, level);
	}
	
	if (m_AvatarY <= 0.f)
	{
		m_ActionState = AvatarState::ActionState::dead;
	}

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
		if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			avatarState->GetCurrentAvatar()->SetAvatarHeight(15.f);
		}
		
		//avatarState->GetCurrentAvatar()->GetAvatarHeight();
		if (!CheckKeys() && m_IsOnGround)
		{
			SetActionState(AvatarState::ActionState::waiting);
			if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
			{
				avatarState->GetCurrentAvatar()->SetAvatarHeight(30.f);
			}
		}
		else if (!CheckKeyDown())
		{
			SetActionState(AvatarState::ActionState::jumping);
			if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
			{
				avatarState->GetCurrentAvatar()->SetAvatarHeight(30.f);
			}
		}
		else
		{
			SetActionState(AvatarState::ActionState::ducking);
		}
	}
	if (m_ActionState == AvatarState::ActionState::dead)
	{
		if (m_AvatarY <= 0.f)
		{
			m_ActionState = AvatarState::ActionState::moving;
			m_AvatarX = 10.f;
			m_AvatarY = 272.f;
		}
		

	}
	if (m_ActionState == AvatarState::ActionState::isGoingTroughPipe)
	{
		m_ActionState = AvatarState::ActionState::waiting;
		//m_TimerGoingInPipe -= elapsedSec;
		/*if (m_TimerGoingInPipe <= 0.f)
		{
			m_ActionState = AvatarState::ActionState::waiting;
		}
		std::cout << m_TimerGoingInPipe << std::endl;*/
	}
	UpdatePosition(elapsedSec, cameraPos);
	if (m_AmmoCounterAmound >= 2)
	{
		m_AmmoCounterAmound = 2;
	}
	
	if (m_RealoadingCounter <= 0.f)
	{
		m_RealoadingCounter = 0.6;	
		m_AmmoCounterAmound++;
	}
	else
	{
		if (m_AmmoCounterAmound < 2)
		{
			m_RealoadingCounter = m_RealoadingCounter - elapsedSec;
		}		
	}

	if (m_CanBeHit == false)
	{
		m_TimerCanBeHit = m_TimerCanBeHit - elapsedSec;
		//std::cout << m_TimerCanBeHit << std::endl;
		if (m_TimerCanBeHit <= 0)
		{
			m_TimerCanBeHit = m_TimeToHitAgain;
			m_CanBeHit = true;
		}
	}
	
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
		if (m_ActionState != AvatarState::ActionState::dead)
		{
			if (m_AvatarX <= cameraPos.x - Window().width / 2 + 20.f)
			{
				m_AvatarX = cameraPos.x - Window().width / 2 + 20.f;
				m_Velocity.x = -1;
			}
		}
	}
	
	
}

void AvatarState::HandleKeys(float elapsedSec, Level* level)
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
		m_SoundEffectMarioJump->SetVolume(10);
		if (m_IsOnGround)
		{

			m_SoundEffectMarioJump->Play(false);
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
			//m_AvatarHeight
			//SetAvatarHeight();
		}
	} 
	if (pStates[SDL_SCANCODE_SPACE])
	{
		if (GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			if (m_ActionState != ActionState::ducking)
			{
				if (m_AmmoCounterAmound >= 1)
				{
					level->AddLiveItem(new Projectile(Point2f(m_AvatarX, m_AvatarY + 10.f)));
					m_AmmoCounterAmound--;
				}
			}		
		}
	}
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

bool AvatarState::GetCanBeHit() const
{
	return m_CanBeHit;
}


void AvatarState::TravelTo(Point2f* travelToPosition, PrepareForTravelAnimation prepareForTravelAnimation) {
	m_AvatarX = travelToPosition->x;
	m_AvatarY = travelToPosition->y;
	SetVelocityYAvatar(-10);
	SetVelocityXCollisionAvatar(0);
//	m_pAvatarState->TravelTo(Positie, GoDown / GoUp / GoLeft / GoRight);
}
