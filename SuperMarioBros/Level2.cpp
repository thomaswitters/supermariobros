#include "pch.h"
#include "Level2.h"

Level2::Level2() : Level("Images/Super Mario bros.png", { "Images/SuperMarioBros.svg", "Images/SuperMarioBros2.svg", "Images/SuperMarioBros3.svg", "Images/SuperMarioBros4.svg", "Images/SuperMarioBros5.svg" })
{

}

Level2::~Level2()
{

}

bool Level2::HasReachedEnd(const Rectf& actorShape)
{
	return false;
}