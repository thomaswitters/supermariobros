#include "pch.h"
#include "GameState.h"

GameState::GameState():
	m_NormalMan{ new NormalMan() }
	, m_BiggerMan{ new BiggerMan() }
	, m_FlowerMan{ new FlowerMan() }
	, m_AvatarState{}
	

{
	m_AvatarState = new AvatarState(m_NormalMan);
}

GameState::~GameState() {
	if (m_AvatarState) {
		delete m_AvatarState;
		m_AvatarState = NULL;
	}
	if (m_NormalMan) {
		delete m_NormalMan;
		m_NormalMan = NULL;
	}
	if (m_BiggerMan) {
		delete m_BiggerMan;
		m_BiggerMan = NULL;
	}
	if (m_FlowerMan) {
		delete m_FlowerMan;
		m_FlowerMan = NULL;
	}
	
}

void GameState::DrawAvatar() const {
	m_AvatarState->GetCurrentAvatar()->Draw(m_AvatarState);
}
AvatarState* GameState::GetAvatarState() const
{
	return m_AvatarState;
}
void GameState::UpdateAvatar(float elapsedSec, Level* level, Point2f cameraPos) {
	m_AvatarState->Update(elapsedSec, m_AvatarState, level, cameraPos);
}
void GameState::UpdateDrawAvatar(float elapsedSec) {
	m_AvatarState->GetCurrentAvatar()->UpdateDraw(elapsedSec);
}

void GameState::LevelWon() {
	SDL_Event fake;
	fake.type = SDL_QUIT;
	SDL_PushEvent(&fake);
}

NormalMan* GameState::GetNormalMan() {
	return m_NormalMan;
}

FlowerMan* GameState::GetFlowerMan() {
	return m_FlowerMan;
}

BiggerMan* GameState::GetBiggerMan() {
	return m_BiggerMan;
}

void GameState::ResetAvatar() {
	m_AvatarState->ResetAvatar(m_NormalMan);
}
void GameState::SetAvatar(Avatar* newAvatar) {
	m_AvatarState->SetCurrentAvatar(newAvatar);
}
