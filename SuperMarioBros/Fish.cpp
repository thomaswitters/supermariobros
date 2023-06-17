#include "pch.h"
#include "Fish.h"

Fish::Fish(Point2f GameItemPos) : Enemy(GameItemType::FishType, "Images/smb_enemies_sheet.png", 30, 30, GameItemPos, 16, 16, true, LiveItemState::Alive,
	Vector2f{ -40.f, 0.f}, Vector2f{0.0f, -581.0f},
	2, 6, 2, 0.2f, 3, 6, 15, 7, "Sounds/Goomba.mp3")
	, m_SecFishFloats{3}
	, m_JumpHeight{ ((rand() % 90) + 90.f) }
{
	m_DyingCounter = ((rand() % 2) + 1.f);
}
Fish::~Fish() {
}

void Fish::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	switch (m_LiveItemState) {
	case LiveItemState::Alive:
	{
		m_AnimTime += elapsedSec;
		int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
		m_AnimFrame = totalFramesElapsed % m_NrOfFrames;

		SetVelocityEnemy(m_Acceleration, elapsedSec);
		SetPositionVelocity(m_Velocity, elapsedSec);
		
		m_DyingCounter = m_DyingCounter + elapsedSec;
		
		if (m_DyingCounter >= m_SecFishFloats)
		{
			m_JumpHeight = ((rand() % 90) + 90.f);
			m_Velocity.y = float(sqrt(2.0f * 981.f * m_JumpHeight));
			m_DyingCounter = -1.f;
			m_Velocity.x = m_Velocity.x * (-1);
		}
		else if (GetGameItemPos().y <= -40.f)
		{
			m_Velocity.y = float(sqrt(2.0f * 981.f * 10.f));
		}
		break;
	}
	case LiveItemState::Dying:
	{
		m_DyingCounter = m_DyingCounter + elapsedSec;
		if (m_DyingCounter > 1.f)
		{
			m_LiveItemState = LiveItemState::Dead;
			SetActivefalse();
		}
		break;
	}
	}
}