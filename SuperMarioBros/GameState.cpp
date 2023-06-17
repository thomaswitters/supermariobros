#include "pch.h"
#include "GameState.h"
#include "NormalMan.h"
#include "BiggerMan.h"
#include "FlowerMan.h"
#include "Level1.h"
#include "Level2.h"

GameState::GameState():
	m_pNormalMan{ new NormalMan() }
	, m_pBiggerMan{ new BiggerMan() }
	, m_pFlowerMan{ new FlowerMan() }
	, m_pAvatarState{}
	, m_AmountOfLives{3}
	, m_AmountCoins{80}
	, m_pLevels{}
	, m_SoundEffectMarioDies{ new SoundEffect("Sounds/MarioDies2.mp3") }
	, m_CurrentLevel{0}
	, m_MaxTimer{400.f}
	, m_TimerGame{400.f}
	, m_MaxCoins{100}
	, m_AmountOfPoints{00000}
	

{
	m_pLevels.push_back(new Level1());
	m_pLevels.push_back(new Level2());
	m_pAvatarState = new AvatarState(m_pNormalMan);
}

GameState::~GameState() {
	//m_pLevels! loop over the levels and delete!

	for (size_t i = 0; i < m_pLevels.size(); i++)
	{
		Level* Level = m_pLevels[i];
		delete Level;
	}
	m_pLevels.clear();
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

void GameState::UpdateHud(float elapsedSec)
{
	SetTimer(elapsedSec);
	if (GetAmountCoins() >= m_MaxCoins)
	{
		SetAmountCoins(0);
		IncreaseAmountOfLives();
	}
}

void GameState::LevelWon() {
	if (m_CurrentLevel < m_pLevels.size()) {
		// reset the current level, just in case we would return
		
		PlayerResurrects();
		//m_pAvatarState->SetActionState(AvatarState::ActionState::respawning);
		GetLevel()->ResetLevel();
		if (m_CurrentLevel < 1)
		{
			m_CurrentLevel++;
		}
		else
		{
			QuitGame();
		}
		
	} 
	else
	{
		QuitGame();
	}
		
}

void GameState::QuitGame() {
	SDL_Event fake;
	fake.type = SDL_QUIT;
	SDL_PushEvent(&fake);
}

void GameState::PlayerDies() {
	m_SoundEffectMarioDies->SetVolume(30);
	m_SoundEffectMarioDies->Play(false);
	DecreaseAmountOfLives();
	//m_pAvatarState->SetActionState(AvatarState::ActionState::dead);
	if (m_AmountOfLives <= 0) {
		QuitGame();
	}
	else {
		m_pAvatarState->SetActionState(AvatarState::ActionState::dead);
	}
}
void GameState::PlayerResurrects() {	
	GetLevel()->ResetLevel();
	//SetAvatar(GetNormalMan());
	ResetTimer();
	if (m_CurrentLevel < 1)
	{
		m_pAvatarState->SetPositionYAvatar(272.f);
		m_pAvatarState->SetPositionXAvatar(50.f);
	}
	else
	{
		m_pAvatarState->SetPositionYAvatar(10.f);
		m_pAvatarState->SetPositionXAvatar(50.f);
	}
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

