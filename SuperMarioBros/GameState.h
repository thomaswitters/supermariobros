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
		return m_Level;
	}
private:
	AvatarState* m_AvatarState;

	// TODO: move to AvatarState
	NormalMan* m_NormalMan;
	BiggerMan* m_BiggerMan;
	FlowerMan* m_FlowerMan;
	// TODO: end move to AvatarState
	Level* m_Level{};
};

