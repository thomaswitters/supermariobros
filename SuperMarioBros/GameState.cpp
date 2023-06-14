#include "pch.h"
#include "GameState.h"
#include "NormalMan.h"
#include "BiggerMan.h"
#include "FlowerMan.h"
#include "Level1.h"

GameState::GameState():
	m_pNormalMan{ new NormalMan() }
	, m_pBiggerMan{ new BiggerMan() }
	, m_pFlowerMan{ new FlowerMan() }
	, m_pAvatarState{}
	, AmountOfLives{3}
	, m_AmountCoins{0}
	, m_pLevels{}
	, m_SoundEffectMarioDies{ new SoundEffect("Sounds/MarioDies.mp3") }
	

{
	//m_pLevels.push_back(new Level1());
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
	
	if (m_SoundEffectMarioDies) {
		delete m_SoundEffectMarioDies;
		m_SoundEffectMarioDies = NULL;
	}
}
void GameState::DrawAvatar() const {
	m_pAvatarState->GetCurrentAvatar()->Draw(m_pAvatarState);
}
AvatarState* GameState::GetAvatarState() const
{
	return m_pAvatarState;
}
void GameState::UpdateAvatar(float elapsedSec, Level* level, Point2f cameraPos, GameState* gameState) {
	m_pAvatarState->Update(elapsedSec, gameState, level, cameraPos);
}
void GameState::UpdateDrawAvatar(float elapsedSec) {
	m_pAvatarState->GetCurrentAvatar()->UpdateDraw(elapsedSec);
}
void GameState::UpdateItemsLevel(float elapsedSec, Point2f cameraPos, GameState* gameState)
{
	GetLevel()->UpdateItems(elapsedSec, gameState, cameraPos);
	
}

void GameState::LevelWon() {
	SDL_Event fake;
	fake.type = SDL_QUIT;
	SDL_PushEvent(&fake);
}
bool GameState::GoToLevel2(bool reachedLevel1){
	return reachedLevel1;
}
void GameState::ResetLevel(Level* level) {
	level->ResetLevel();
}

void GameState::PlayerDies() {
	m_SoundEffectMarioDies->SetVolume(30);
	m_SoundEffectMarioDies->Play(false);
	SetAmountOfLives();
	if (AmountOfLives <= 0) {
	//	game over
	}
	else {
		m_pAvatarState->SetActionState(AvatarState::ActionState::dead);
	}
}

void GameState::PlayerResurrects(Level* level) {
	ResetLevel(level);

	m_pAvatarState->SetPositionYAvatar(272.f);
	m_pAvatarState->SetPositionXAvatar(50.f);
	m_pAvatarState->SetActionState(AvatarState::ActionState::respawning);
	
}

Avatar* GameState::GetNormalMan() {
	return m_pNormalMan;
}
Avatar* GameState::GetFlowerMan() {
	return m_pFlowerMan;
}
Avatar* GameState::GetBiggerMan() {
	return m_pBiggerMan;
}
void GameState::ResetAvatar() {
	m_pAvatarState->ResetAvatar(m_pNormalMan);
}
void GameState::SetAvatar(Avatar* newAvatar) {
	m_pAvatarState->SetCurrentAvatar(newAvatar);
}

