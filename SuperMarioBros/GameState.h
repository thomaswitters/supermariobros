#pragma once

#include "AvatarState.h"
#include "Avatar.h"
#include "Level.h"
#include <vector>
#include <SoundEffect.h>

 //I had to choose between 
 //
 //- allowing to create Avatar instancs from GameElements
 //- or to use hardcoded instances of Avatar in GameState.
 //
 //The first has the advantage of being more flexible, more plugable: it allows for example to be able to extend the game 
 //with GameElements which create an instance of an Avatar specific to that GameElement. However, it would also mean I needed 
 //to cleanup these instances of Avatar
 //
 //I have chosen to create instances of Avatar in GameState, which makes it easier to maintain, no need to cleanup.
 //It is not as flexible / plugable but I did not see that required at the moment.

class Avatar;
class AvatarState;
class Level;
class Level1;

class GameState
{
public:
	GameState();

	/*GameState(const GameState& other) {	 // II. Copy constructor
		m_pAvatarState = other.m_pAvatarState;
		
		copyToMe(other);
	}

	GameState& operator=(const GameState& other) // III. copy assignment
	{
		if (this == &other)
			return *this;

		copyToMe(other);
		return *this;
	}

	void copyToMe(const GameState& other)
	{
		m_pNormalMan = other.m_pNormalMan;
	}
	*/
	virtual ~GameState();  // I. desctructor

	/*
	GameState(GameState&& other) noexcept // IV. move constructor
	{
		copyToMe
	}
	*/

	void LevelWon();

	// TODO: move to AvatarState
	Avatar* GetNormalMan();
	Avatar* GetBiggerMan();
	Avatar* GetFlowerMan();
	void ResetAvatar();

	void PlayerDies();
	void PlayerResurrects();

	void SetAvatar(Avatar* newAvatar);
	// TODO: end move to AvatarState

	void DrawAvatar() const;
	AvatarState* GetAvatarState() const;
	void UpdateAvatar(float elapsedSec, Level* level, Point2f cameraPos, GameState* gameState);
	void UpdateDrawAvatar(float elapsedSec);

	void UpdateHud(float elapsedSec);

	void QuitGame();

	void UpdateItemsLevel(float elapsedSec, Point2f cameraPos, GameState* gameState);

	Level* GetLevel() const
	{
		return m_pLevels.at(m_CurrentLevel);
	}

	int GetPointsGame()
	{
		return m_AmountOfPoints;
	}
	void SetAmountPointsPlus(int amount)
	{
		m_AmountOfPoints = GetPointsGame() + amount;
	}

	int GetAmountOfLives()
	{
		return m_AmountOfLives;
	}
	void DecreaseAmountOfLives()
	{
		if (m_AmountOfLives > 0)
		{
			m_AmountOfLives = GetAmountOfLives() - 1;
		}
	}
	void IncreaseAmountOfLives()
	{
		m_AmountOfLives = GetAmountOfLives() + 1;
	}
	float GetTimerGame()
	{
		return m_TimerGame;
	}
	void SetTimer(float elapsedSec)
	{
		m_TimerGame -= elapsedSec;
	}
	void ResetTimer()
	{
		m_TimerGame = m_MaxTimer;
	}
	int GetAmountCoins()
	{
		return m_AmountCoins;
	}
	int GetCurrentLevel()
	{
		return m_CurrentLevel;
	}
	void SetAmountCoinsPlus(int amount)
	{
		m_AmountCoins = GetAmountCoins() + amount;
	}
	void SetAmountCoins(int amount)
	{
		m_AmountCoins = amount;
	}

private:
	AvatarState* m_pAvatarState;

	// TODO: move to AvatarState
	Avatar* m_pNormalMan;
	Avatar* m_pBiggerMan;
	Avatar* m_pFlowerMan;
	// TODO: end move to AvatarState
	std::vector<Level*> m_pLevels;
	int m_CurrentLevel;

	int m_AmountOfLives;
	int m_AmountCoins;
	float m_TimerGame;
	float m_MaxTimer;
	int m_AmountOfPoints;

	SoundEffect* m_SoundEffectMarioDies;
	int m_MaxCoins;
};

