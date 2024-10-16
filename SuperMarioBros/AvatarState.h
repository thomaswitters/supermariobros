#pragma once

#include "Avatar.h"
#include <Vector2f.h>
#include "Level.h"
#include <SoundEffect.h>

class Level;
class Avatar;

enum PrepareForTravelAnimation {
	FallDown, RiseUp, GoLeft, GoRight
};

class AvatarState
{
public:
	AvatarState(Avatar* initialAvatar);
	virtual ~AvatarState();
	void SetCurrentAvatar(Avatar* currentAvatar);
	Avatar* GetCurrentAvatar() const;
	void ResetAvatar(Avatar* normalMan);
	Point2f GetPositionAvatar() const;
	void SetPositionVelosityAvatar(Vector2f m_Velocity, float elapsedSec);
	void SetPositionYAvatar(float y);
	void SetPositionXAvatar(float x);
	void SetPositionXCollisionLeftAvatar(float x, float width);
	void SetPositionXCollisionRightAvatar(float x, float width);
	void SetPositionYCollisionBottomAvatar(float y, float height);
	void SetPositionYCollisionTopAvatar(float y, float height);

	Vector2f GetVelocityAvatar() const;
	void SetVelocityAvatar(Vector2f m_Acceleration, float elapsedSec);
	void SetVelocityPosXAvatar(float x);
	void SetVelocityJumpAvatar(float Y);
	void SetVelocityYAvatar(float Y);
	void SetVelocityXCollisionAvatar(float x);
	void SetVelocityYCollisionBottomAvatar();
	void SetVelocityYCollisionTopAvatar();

	Vector2f GetAccelerationAvatar();
	enum class ActionState {
		waiting,
		moving,
		jumping,
		ducking,
		stopping,
		dead,
		isGoingTroughPipe,
		grabing,
		respawning,
		endLevel
	};

	ActionState GetActionState() const;
	void SetActionState(ActionState actionState);

	void Update(float elapsedSec, GameState* gameState, Level* level, Point2f cameraPos);
	void UpdatePosition(float elapsedSec, Point2f cameraPos);
	void HandleKeys(float elapsedSec, Level* level);
	bool CheckKeys();
	bool CheckKeyDown();

	
	void SetIsJumpingfalse()
	{
		m_IsJumping = false;
	}
	bool GetCanBeHit() const;

	void TravelTo(Point2f* travelToPosition, PrepareForTravelAnimation prepareForTravelAnimation);
private:
	float m_AvatarX;
	float m_AvatarY;
	Vector2f m_Velocity{};
	Vector2f m_Acceleration{};
	bool m_IsOnGround{};

	Avatar* m_pCurrentAvatar;
	ActionState m_ActionState{ ActionState::moving };

	float m_CountStartJump;
	float m_JumpTime;
	bool m_IsJumping;
	int m_AmmoCounterAmound;
	float m_RealoadingCounter;

	bool m_CanBeHit;
	float m_TimeToHitAgain;
	float m_TimerCanBeHit;

	float m_TimerGoingInPipe;
	
	SoundEffect* m_SoundEffectMarioJump;
	SoundEffect* m_SoundEffectMarioFinnish;

	float m_FlagPoleHeight;
	float m_FlagPoleHeightLevel1;
	float m_FlagPoleHeightLevel2;
	float m_EndLevel;
	float m_EndLevel1;
	float m_EndLevel2;

	float m_FlagPolePos;
	float m_FlagPolePosLevel1;
	float m_FlagPolePosLevel2;
};
