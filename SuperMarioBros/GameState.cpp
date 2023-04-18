#include "pch.h"
#include "GameState.h"

GameState::GameState():
	m_pNormalMan{ new NormalMan() }
	, m_pBiggerMan{ new BiggerMan() }
	, m_pFlowerMan{ new FlowerMan() }
	, m_pAvatarState{}
	

{
	m_pAvatarState = new AvatarState(m_pNormalMan);
}
GameState::~GameState() {
	if (m_pAvatarState) {
		delete m_pAvatarState;
		m_pAvatarState = NULL;
	}
	if (m_pNormalMan) {
		delete m_pNormalMan;
		m_pNormalMan = NULL;
	}
	if (m_pBiggerMan) {
		delete m_pBiggerMan;
		m_pBiggerMan = NULL;
	}
	if (m_pFlowerMan) {
		delete m_pFlowerMan;
		m_pFlowerMan = NULL;
	}
	
}
void GameState::DrawAvatar() const {
	m_pAvatarState->GetCurrentAvatar()->Draw(m_pAvatarState);
}
AvatarState* GameState::GetAvatarState() const
{
	return m_pAvatarState;
}
void GameState::UpdateAvatar(float elapsedSec, Level* level, Point2f cameraPos) {
	m_pAvatarState->Update(elapsedSec, m_pAvatarState, level, cameraPos);
}
void GameState::UpdateDrawAvatar(float elapsedSec) {
	m_pAvatarState->GetCurrentAvatar()->UpdateDraw(elapsedSec);
}
void GameState::LevelWon() {
	SDL_Event fake;
	fake.type = SDL_QUIT;
	SDL_PushEvent(&fake);
}
NormalMan* GameState::GetNormalMan() {
	return m_pNormalMan;
}
FlowerMan* GameState::GetFlowerMan() {
	return m_pFlowerMan;
}
BiggerMan* GameState::GetBiggerMan() {
	return m_pBiggerMan;
}
void GameState::ResetAvatar() {
	m_pAvatarState->ResetAvatar(m_pNormalMan);
}
void GameState::SetAvatar(Avatar* newAvatar) {
	m_pAvatarState->SetCurrentAvatar(newAvatar);
}
