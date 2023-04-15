#include "pch.h"
#include "Level1.h"

Level1::Level1() : Level("Images/Super Mario bros.png", { "Images/SuperMarioBros.svg", "Images/SuperMarioBros2.svg", "Images/SuperMarioBros3.svg", "Images/SuperMarioBros4.svg" })
{
	
	
	AddGameItem(new Coin(Point2f(256.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(256.f, 320.f)));
	AddGameItem(new PowerUp(Point2f(336.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(336.f, 320.f)));
	AddGameItem(new Coin(Point2f(368.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(368.f, 320.f)));

	AddGameItem(new Coin(Point2f(352.f, 384.f)));
	AddGameItem(new QuestionBlock(Point2f(352.f, 384.f)));

	AddGameItem(new DecorBlock(Point2f(320.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(352.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(384.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(1232.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(1264.f, 320.f)));

	AddGameItem(new DecorBlock(Point2f(1280.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1296.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1312.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1328.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1344.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1360.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1376.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1392.f, 384.f)));

	AddGameItem(new NormalBlock(Point2f(320.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(352.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(384.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(1232.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(1264.f, 320.f)));

	AddGameItem(new NormalBlock(Point2f(1280.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1296.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1312.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1328.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1344.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1360.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1376.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1392.f, 384.f)));

	AddGameItem(new Pipe(Point2f(448.f, 272.f), 32.f));
	AddGameItem(new Pipe(Point2f(608.f, 272.f), 47.f));
	AddGameItem(new Pipe(Point2f(736.f, 272.f), 63.f));


	AddGameItem(new FlagPole(Point2f(240.f, 270.f)));

}

Level1::~Level1()
{

}

bool Level1::HasReachedEnd(const Rectf& actorShape)
{
	return false;
}