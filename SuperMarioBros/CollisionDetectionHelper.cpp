#include "pch.h"
#include "CollisionDetectionHelper.h"
#include <iostream>

CollisionDetectionHelper::CollisionLocation CollisionDetectionHelper::determineCollisionDir(Rectf avatarRect, Vector2f RichtingAvatar, Rectf itemRect)
{
	//if (RichtingAvatar.x >= 0.f)
	//{
	//	if (avatarRect.left + avatarRect.width <= itemRect.left + 0.f /*+ itemRect.width*/ && avatarRect.left + avatarRect.width >= itemRect.left && avatarRect.bottom <= itemRect.bottom + itemRect.height && avatarRect.bottom + avatarRect.height >= itemRect.bottom + itemRect.height
	//		|| avatarRect.left + avatarRect.width <= itemRect.left + 0.f/*+ itemRect.width*/ && avatarRect.left + avatarRect.width >= itemRect.left && avatarRect.bottom <= itemRect.bottom && avatarRect.bottom + avatarRect.height >= itemRect.bottom)
	//	{
	//		return CollisionLocation::avatorBumpsOnTheLeft;
	//	}
	//}
	//if (RichtingAvatar.x <= 0.f)
	//{
	//	if (avatarRect.left <= itemRect.left + itemRect.width && avatarRect.left >= itemRect.left + itemRect.width - 2.f && avatarRect.bottom <= itemRect.bottom + itemRect.height && avatarRect.bottom + avatarRect.height >= itemRect.bottom + itemRect.height)
	//	{
	//		return CollisionLocation::avatorBumpsOnTheRight;
	//	}
	//}


	//if (avatarRect.bottom <= itemRect.bottom + itemRect.height && avatarRect.bottom + avatarRect.height >= itemRect.bottom + itemRect.height && avatarRect.left <= itemRect.left + 2.f && avatarRect.left + avatarRect.width >= itemRect.left + 2.f
	//|| avatarRect.bottom <= itemRect.bottom + itemRect.height && avatarRect.bottom + avatarRect.height >= itemRect.bottom + itemRect.height && avatarRect.left + avatarRect.width >= itemRect.left + 2.f && avatarRect.left <= itemRect.left + itemRect.width - 2.f)
	//{
	//	return CollisionLocation::avatorBumpsFromTheTop;
	//}


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
	if (RichtingAvatar.x >= 0.f)// && beweegt ook (naar rechts)
	{
		if (
				(aRight >= iLeft - 0.f) &&
				(aRight <= iRight + 0.f) &&
				(
					((aBottom >= iBottom ) && (aBottom <= iTop - 10.f)) 
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
	if (RichtingAvatar.x <= 0.f)// && beweegt ook(naar links)
	{
		if (
				(aLeft <= iRight + 0.f) &&
				(aLeft >= iLeft - 0.f) &&
				(
					((aBottom >= iBottom ) && (aBottom <= iTop - 10.f))
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
	if (RichtingAvatar.y > 0.f)// && beweegt ook(naar boven)
	{
		if (
				(aTop >= iBottom - 5.f) &&
				(aTop <= iTop) &&
				(
					((aLeft >= iLeft) && (aLeft <= iRight)) 
					||
					((aRight >= iLeft) && (aRight <= iRight))
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
	if (RichtingAvatar.y < 0.f)// && beweegt ook(naar onder)
	{
		if 	(
				(aBottom <= iTop + 10.f) &&
				(aBottom >= iBottom) &&
				(
					((aLeft >= iLeft) && (aLeft <= iRight))
					||
					((aRight >= iLeft) && (aRight <= iRight))
				)
			) 
		{
			return CollisionLocation::avatorBumpsFromTheTop;
		}
	}



	//if (utils::IsOverlapping(avatarRect, itemRect))
	//{
	//	if (RichtingAvatar.x > 0.f)// && beweegt ook (naar rechts)
	//	{

	//		return CollisionLocation::avatorBumpsOnTheLeft;
	//	}
	//	if (RichtingAvatar.x < 0.f)// && beweegt ook(naar links)
	//	{

	//		return CollisionLocation::avatorBumpsOnTheRight;
	//	}

	//	if (RichtingAvatar.y < 0.f)// && beweegt ook(naar onder)
	//	{
	//		return CollisionLocation::avatorBumpsFromTheTop;

	//	}	
	//	if (RichtingAvatar.y > 0.f)
	//	{
	//		return CollisionLocation::avatorBumpsFromTheBottom;

	//	}
	//	
	//}
	//else
	//{
	//	return CollisionLocation::noCollision;
	//}
	
	//}

	//if (avatarRect.left + avatarRect.width >= itemRect.left && itemRect.left + itemRect.width >= avatarRect.left
	//	&& avatarRect.bottom + avatarRect.height >= itemRect.bottom && itemRect.bottom + itemRect.height >= avatarRect.bottom)
	//{
	//	if (RichtingAvatar.x > 0.f)
	//	{
	//		return CollisionLocation::avatorBumpsOnTheRight;
	//	}
	//	if (RichtingAvatar.x < 0.f)
	//	{
	//		return CollisionLocation::avatorBumpsOnTheLeft;
	//	}

	//	if (RichtingAvatar.y >= 0.f)
	//	{
	//		return CollisionLocation::avatorBumpsFromTheBottom;
	//	}
	//	if (RichtingAvatar.y <= 0.f)
	//	{
	//		return CollisionLocation::avatorBumpsFromTheTop;
	//	}
	//}






	/*Point2f origin1{ avatarRect.left, avatarRect.bottom + avatarRect .height};
	Point2f origin2{ avatarRect.left + avatarRect.width, avatarRect.bottom};

	utils::HitInfo
	hitInfo{};

	std::vector<Point2f> m_VerticesItemleft = { Point2f(itemRect.left, itemRect.bottom), Point2f(itemRect.left, itemRect.bottom + itemRect.height) };
	std::vector<Point2f> m_VerticesItemRight = { Point2f(itemRect.left + itemRect.width,itemRect.bottom), Point2f(itemRect.left + itemRect.width, itemRect.bottom + itemRect.height) };


	if (utils::Raycast(m_VerticesItemleft, origin1, origin2, hitInfo))
	{
		return CollisionLocation::avatorBumpsOnTheRight;
	}
	if (utils::Raycast(m_VerticesItemRight, origin1, origin2, hitInfo))
	{
		return CollisionLocation::avatorBumpsOnTheLeft;
	}*/
	
	/*else if (RichtingAvatar.y >= 0.f)
	{
		if (avatarRect.bottom + avatarRect.height >= itemRect.bottom && avatarRect.bottom + avatarRect.height <= itemRect.bottom + itemRect.height && avatarRect.left + 1.f >= itemRect.left && avatarRect.left + 1.f <= itemRect.left + itemRect.width || avatarRect.left + avatarRect.width - 1.f >= itemRect.left && avatarRect.left + avatarRect.width - 1.f <= itemRect.left + itemRect.width && avatarRect.bottom + avatarRect.height >= itemRect.bottom && avatarRect.bottom + avatarRect.height <= itemRect.bottom + itemRect.height)
		{
			return CollisionLocation::avatorBumpsFromTheBottom;
		}
	}*/

	
	/*else if (RichtingAvatar.x < 0.f)
	{
		if (avatarRect.left <= itemRect.left + itemRect.width && avatarRect.left >= itemRect.left && avatarRect.bottom >= itemRect.bottom && avatarRect.bottom <= itemRect.bottom + itemRect.height || avatarRect.left <= itemRect.left + itemRect.width && avatarRect.left >= itemRect.left && avatarRect.bottom + avatarRect.height >= itemRect.bottom + 2.f && avatarRect.bottom + avatarRect.height <= itemRect.bottom + itemRect.height)
		{
			return CollisionLocation::avatorBumpsOnTheLeft;
		}
	}*/
	

	//|| avatarRect.left + avatarRect.width >= itemRect.left - 2.f && avatarRect.left + 2.f /* + avatarRect.width*/ <= itemRect.left + itemRect.width && avatarRect.bottom + avatarRect.height >= itemRect.bottom + 2.f && avatarRect.bottom + avatarRect.height <= itemRect.bottom + itemRect.height

	
	//return CollisionLocation::noCollision;

	/*avatarRect.left + avatarRect.width >= itemRect.left && avatarRect.left <= itemRect.left + itemRect.width*/
	
	
	
	
}
