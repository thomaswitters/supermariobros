#pragma once
#include <Vector2f.h>
#include <utils.h>
class CollisionDetectionHelper
{
public:

	enum class CollisionLocation {
		avatorBumpsOnTheRight,
		avatorBumpsOnTheLeft,
		avatorBumpsFromTheBottom,
		avatorBumpsFromTheTop,
		avatorBumpsOnTheLeftTop,
		noCollision
	};

	static CollisionLocation determineCollisionDir(Rectf avatarRect, Vector2f RichtingAvatar, Rectf itemRect);
};
