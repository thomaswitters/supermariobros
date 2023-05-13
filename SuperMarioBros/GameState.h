#pragma once

#include "AvatarState.h"
#include "Avatar.h"
#include "Level.h"
#include <vector>

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
class NormalMan;
class BiggerMan;
class FlowerMan;
class AvatarState;
class Level;
class Level1;

class GameState
{
public:
	GameState();
	virtual ~GameState();

	void LevelWon();

	// TODO: move to AvatarState
	NormalMan* GetNormalMan();
	BiggerMan* GetBiggerMan();
	FlowerMan* GetFlowerMan();
	void ResetAvatar();
	void SetAvatar(Avatar* newAvatar);
	// TODO: end move to AvatarState

	void DrawAvatar() const;
	AvatarState* GetAvatarState() const;
	void UpdateAvatar(float elapsedSec, Level* level, Point2f cameraPos);
	void UpdateDrawAvatar(float elapsedSec);

	Level* GetLevel() const
	{
		return m_pLevel;
	}

	void SetLevel(Level* level) {
		m_pLevel = level;
	}

	int GetAmountOfLives()
	{
		return AmountOfLives;
	}

	void SetAmountOfLives()
	{
		AmountOfLives = GetAmountOfLives() - 1;
	}


	int GetAmountCoins()
	{
		return m_AmountCoins;
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
	NormalMan* m_pNormalMan;
	BiggerMan* m_pBiggerMan;
	FlowerMan* m_pFlowerMan;
	// TODO: end move to AvatarState
	Level* m_pLevel{};
	int AmountOfLives;
	int m_AmountCoins;
};

