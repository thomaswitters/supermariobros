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

	AddGameItem(new PowerUp(Point2f(1248.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(1248.f, 320.f)));

	AddGameItem(new Coin(Point2f(1504.f, 384.f)));
	AddGameItem(new QuestionBlock(Point2f(1504.f, 384.f)));

	AddGameItem(new Coin(Point2f(1696.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(1696.f, 320.f)));

	AddGameItem(new Coin(Point2f(1744.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(1744.f, 320.f)));

	AddGameItem(new PowerUp(Point2f(1744.f, 384.f)));
	AddGameItem(new QuestionBlock(Point2f(1744.f, 384.f)));

	AddGameItem(new Coin(Point2f(1792.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(1792.f, 320.f)));

	AddGameItem(new Coin(Point2f(2064.f, 384.f)));
	AddGameItem(new QuestionBlock(Point2f(2064.f, 384.f)));

	AddGameItem(new Coin(Point2f(2080.f, 384.f)));
	AddGameItem(new QuestionBlock(Point2f(2080.f, 384.f)));

	AddGameItem(new Coin(Point2f(2720.f, 320.f)));
	AddGameItem(new QuestionBlock(Point2f(2720.f, 320.f)));


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

	AddGameItem(new DecorBlock(Point2f(1440.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1456.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1472.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1488.f, 384.f)));

	AddGameItem(new DecorBlock(Point2f(1504.f, 320.f)));

	AddGameItem(new DecorBlock(Point2f(1584.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(1600.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(1616.f, 320.f)));

	AddGameItem(new DecorBlock(Point2f(1888.f, 320.f)));

	AddGameItem(new DecorBlock(Point2f(1936.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1952.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(1968.f, 384.f)));

	AddGameItem(new DecorBlock(Point2f(2048.f, 384.f)));
	AddGameItem(new DecorBlock(Point2f(2096.f, 384.f)));

	AddGameItem(new DecorBlock(Point2f(2064.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(2080.f, 320.f)));

	AddGameItem(new DecorBlock(Point2f(2688.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(2704.f, 320.f)));
	AddGameItem(new DecorBlock(Point2f(2736.f, 320.f)));


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

	AddGameItem(new NormalBlock(Point2f(1440.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1456.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1472.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1488.f, 384.f)));

	AddGameItem(new NormalBlock(Point2f(1504.f, 320.f)));

	AddGameItem(new NormalBlock(Point2f(1584.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(1600.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(1616.f, 320.f)));

	AddGameItem(new NormalBlock(Point2f(1888.f, 320.f)));

	AddGameItem(new NormalBlock(Point2f(1936.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1952.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(1968.f, 384.f)));

	AddGameItem(new NormalBlock(Point2f(2048.f, 384.f)));
	AddGameItem(new NormalBlock(Point2f(2096.f, 384.f)));

	AddGameItem(new NormalBlock(Point2f(2064.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(2080.f, 320.f)));

	AddGameItem(new NormalBlock(Point2f(2688.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(2704.f, 320.f)));
	AddGameItem(new NormalBlock(Point2f(2736.f, 320.f)));


	AddGameItem(new ConcreteBlock(Point2f(2144.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2160.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2160.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2176.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2176.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2176.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2192.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2192.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2192.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2192.f, 320)));

	AddGameItem(new ConcreteBlock(Point2f(2240.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2240.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2240.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2240.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2256.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2256.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2256.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2272.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2272.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2288.f, 272)));

	AddGameItem(new ConcreteBlock(Point2f(2368.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2384.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2384.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2400.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2400.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2400.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2416.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2416.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2416.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2416.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2432.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2432.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2432.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2432.f, 320)));

	AddGameItem(new ConcreteBlock(Point2f(2480.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2480.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2480.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2480.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2496.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2496.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2496.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2512.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2512.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2528.f, 272)));

	AddGameItem(new ConcreteBlock(Point2f(2896.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2912.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2912.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2928.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2928.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2928.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2944.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2944.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2944.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2944.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2960.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2960.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2960.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2960.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2960.f, 336)));
	AddGameItem(new ConcreteBlock(Point2f(2976.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2976.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2976.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2976.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2976.f, 336)));
	AddGameItem(new ConcreteBlock(Point2f(2976.f, 352)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 336)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 352)));
	AddGameItem(new ConcreteBlock(Point2f(2992.f, 368)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 336)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 352)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 368)));
	AddGameItem(new ConcreteBlock(Point2f(3008.f, 384)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 272)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 288)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 304)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 320)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 336)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 352)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 368)));
	AddGameItem(new ConcreteBlock(Point2f(3024.f, 384)));


	AddGameItem(new Pipe(Point2f(448.f, 272.f), 32.f));
	AddGameItem(new Pipe(Point2f(608.f, 272.f), 47.f));
	AddGameItem(new Pipe(Point2f(736.f, 272.f), 63.f));
	AddGameItem(new Pipe(Point2f(912.f, 272.f), 63.f));
	AddGameItem(new Pipe(Point2f(2608.f, 272.f), 32.f));
	AddGameItem(new Pipe(Point2f(2864.f, 272.f), 32.f));

	AddGameItem(new FlagPole(Point2f(3174.f, 288.f)));
	AddGameItem(new ConcreteBlock(Point2f(3168.f, 272)));
	AddLiveItem(new Goomba(Point2f(300.f, 272.f)));
	AddLiveItem(new Goomba(Point2f(650.f, 272.f)));
	AddLiveItem(new Goomba(Point2f(750.f, 272.f)));

	AddLiveItem(new Goomba(Point2f(1280.f, 400.f)));
	AddLiveItem(new Goomba(Point2f(1312.f, 400.f)));

	AddLiveItem(new Goomba(Point2f(1530.f, 272.f)));
	AddLiveItem(new Goomba(Point2f(1550.f, 272.f)));

	AddLiveItem(new Goomba(Point2f(1840.f, 272.f)));
	AddLiveItem(new Goomba(Point2f(1860.f, 272.f)));

	AddLiveItem(new Goomba(Point2f(1960.f, 272.f)));
	AddLiveItem(new Goomba(Point2f(1980.f, 272.f)));

	AddLiveItem(new Goomba(Point2f(2040.f, 272.f)));
	AddLiveItem(new Goomba(Point2f(2060.f, 272.f)));

	
}

Level1::~Level1()
{

}

bool Level1::HasReachedEnd(const Rectf& actorShape)
{
	return false;
}