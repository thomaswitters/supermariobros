#include "pch.h"
#include "Goomba.h"

Goomba::Goomba(Point2f GameItemPos) : Enemy(GameItemType::GoombaType, "Images/smb_enemies_sheet.png", 30, 30, GameItemPos, 16, 16, true, LiveItemState::Alive,
	Vector2f{-30.0f, 0.f}, Vector2f{0.0f, -581.0f},
	0, 0, 2, 0.2f, 2, 0, 15, 7, "Sounds/Goomba.mp3")
{
	
}
Goomba::~Goomba() {
}

void Goomba::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	switch (m_LiveItemState) {
	case LiveItemState::Alive:
	{
		m_AnimTime += elapsedSec;
		int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
		m_AnimFrame = totalFramesElapsed % m_NrOfFrames;

		SetVelocityEnemy(m_Acceleration, elapsedSec);
		/*m_Velocity += m_Acceleration * elapsedSec;  */
		SetPositionVelocity(m_Velocity, elapsedSec);
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
