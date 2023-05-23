#include "pch.h"
#include "CollisionDetectionHelper.h"
#include <iostream>

CollisionDetectionHelper::CollisionLocation CollisionDetectionHelper::determineCollisionDir(Rectf avatarRect, Vector2f RichtingAvatar, Rectf itemRect, Vector2f RichtingItem)
{
	
	float aLeft = avatarRect.left;
	float aRight = avatarRect.left + avatarRect.width;
	float aTop = avatarRect.bottom + avatarRect.height;
	float aBottom = avatarRect.bottom;
	float iLeft = itemRect.left;
	float iRight = itemRect.left + itemRect.width;
	float iTop = itemRect.bottom + itemRect.height;
	float iBottom = itemRect.bottom;


	// door te debuggen heb ik gemerkt:
	// "constante gravitatie": blijkbaar is er constante collision met de grond. Telkens wordt het mannetje een klein beetje in de grond geduwd. Collision detecteert dit en duwd het mannetje direct uit de grond
	// Als we nu op een blokje springen dan gebeurt dit mechanisme van gravitatie ook. Als we nu op het uiterste hoekje van een blokje staan (met onze dikke teen), en stilstaan en dan naar rechts drukken
	// dan zorgt die gravitatie ervoor dat we eigenlijk IN het blokje zitten, niet op. Als we dan naar rechts drukken dan detecteert de collision dat we TEGEN het blokje botsen en dan duwen we het mannetje 
	// naar links. Dit zorgt voor foutieve werking / sprong op blokje. 
	// Oplossing 1: kijk naar RichtingAvatar.y < 0.f: dit werkt om op blokje te springen maar dan kunnen we DOOR een blokje springen
	// Oplossing 2: -15.f: dit werkt maar is niet ideaal


	// |AVATAR| -> |RECT|
	if ((RichtingAvatar.x >= 0.f) || (RichtingItem.x < 0.f))// && beweegt ook (naar rechts)
	{
		if (
			(aRight >= iLeft - 0.f) &&
			(aRight <= iRight + 0.f) &&
			(
				((aBottom >= iBottom) && (aBottom <= iTop - 10.f))
				||
				((aTop <= iTop) && (aTop >= iBottom + 10.f))
				||
				((aBottom <= iBottom) && (aTop >= iTop))
				)
			)
		{
			return CollisionLocation::avatorBumpsOnTheLeft;
		}
	}
	// |RECT| <- |AVATAR|
	if ((RichtingAvatar.x <= 0.f) || (RichtingItem.x > 0.f)) // && beweegt ook(naar links)
	{
		if (
			(aLeft <= iRight + 0.f) &&
			(aLeft >= iLeft - 0.f) &&
			(
				((aBottom >= iBottom) && (aBottom <= iTop - 10.f))
				||
				((aTop <= iTop) && (aTop >= iBottom + 10.f))
				||
				((aBottom <= iBottom) && (aTop >= iTop))
				)
			)
		{
			return CollisionLocation::avatorBumpsOnTheRight;
		}
	}

	// |RECT|		
	//    ^
	//    |
	// |AVATAR|
	if ((RichtingAvatar.y > 0.f) || (RichtingItem.y < 0.f))// && beweegt ook(naar boven)
	{
		if (
			(aTop >= iBottom - 5.f) &&
			(aTop <= iTop) &&
			(
				((aLeft >= iLeft +2.f) && (aLeft <= iRight -2.f))
				||
				((aRight >= iLeft+2.f) && (aRight <= iRight -2.f))
				)
			)
		{
			return CollisionLocation::avatorBumpsFromTheBottom;
		}
	}

	//// |AVATAR|
	////     |
	////    \/
	//// |RECT|		
	if ((RichtingAvatar.y < 0.f) || (RichtingItem.y > 0.f)) // && beweegt ook(naar onder)
	{
		if (
			(aBottom <= iTop + 10.f) &&
			(aBottom >= iBottom) &&
			(
				((aLeft >= iLeft + 0.7f) && (aLeft <= iRight - 0.7f))
				||
				((aRight >= iLeft +0.7f) && (aRight <= iRight -0.7f))
				)
			)
		{
			return CollisionLocation::avatorBumpsFromTheTop;
		}
	}

	return CollisionLocation::noCollision;

}
