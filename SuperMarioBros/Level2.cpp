#include "pch.h"
#include "Level2.h"
#include "ConcreteBlock.h"
#include "CoinPickUp.h"
#include "BlueDecorBlock.h"
#include "Fish.h"
#include "PowerUp.h"
#include "QuestionBlock.h"
#include "FlagPole.h"

Level2::Level2() : Level("Images/SuperMariobrosLevel2.png", { "Images/SuperMariobrosLevel2.svg", "Images/SuperMariobrosLevel2_2.svg", "Images/SuperMariobrosLevel2_3.svg", 
	"Images/SuperMariobrosLevel2_4.svg", "Images/SuperMariobrosLevel2_5.svg", "Images/SuperMariobrosLevel2_6.svg", "Images/SuperMariobrosLevel2_7.svg", 
	"Images/SuperMariobrosLevel2_8.svg", "Images/SuperMariobrosLevel2_9.svg", "Images/SuperMariobrosLevel2_10.svg", "Images/SuperMariobrosLevel2_11.svg", 
	"Images/SuperMariobrosLevel2_12.svg", "Images/SuperMariobrosLevel2_13.svg", "Images/SuperMariobrosLevel2_14.svg", "Images/SuperMariobrosLevel2_15.svg", 
	"Images/SuperMariobrosLevel2_16.svg", "Images/SuperMariobrosLevel2_17.svg" })
{
	SetupLevel();
}

Level2::~Level2()
{

}

void Level2::SetupLevel() {

	AddGameItem(new ConcreteBlock(Point2f(160.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(176.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(192.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(208.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(224.f, 32.f)));

	AddGameItem(new ConcreteBlock(Point2f(176.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(192.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(208.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(224.f, 48.f)));

	AddGameItem(new ConcreteBlock(Point2f(192.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(208.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(224.f, 64.f)));


	AddGameItem(new BlueDecorBlock(Point2f(576.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(576.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(592.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(592.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(608.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(608.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(624.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(624.f, 144.f)));
	
	AddGameItem(new BlueDecorBlock(Point2f(880.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(880.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(896.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(896.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(912.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(912.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(928.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(928.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(944.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(944.f, 144.f)));

	AddGameItem(new BlueDecorBlock(Point2f(1168.f, 160.f)));
	AddGameItem(new CoinPickup(Point2f(1168.f, 160.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1152.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1152.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1184.f, 160.f)));
	AddGameItem(new CoinPickup(Point2f(1184.f, 160.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1200.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1200.f, 144.f)));

	AddGameItem(new BlueDecorBlock(Point2f(1552.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1552.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1568.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1568.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1584.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1584.f, 144.f)));

	AddGameItem(new PowerUp(Point2f(1632.f, 144.f)));
	AddGameItem(new QuestionBlock(Point2f(1632.f, 144.f)));

	AddGameItem(new BlueDecorBlock(Point2f(1728.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1728.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1744.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1744.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(1760.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(1760.f, 144.f)));


	AddGameItem(new BlueDecorBlock(Point2f(2128.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(2128.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2144.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(2144.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2160.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(2160.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2176.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(2176.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2192.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(2192.f, 144.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2208.f, 144.f)));
	AddGameItem(new CoinPickup(Point2f(2208.f, 144.f)));

	AddGameItem(new BlueDecorBlock(Point2f(2384.f, 96.f)));
	AddGameItem(new CoinPickup(Point2f(2384.f, 96.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2400.f, 96.f)));
	AddGameItem(new CoinPickup(Point2f(2400.f, 96.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2416.f, 96.f)));
	AddGameItem(new CoinPickup(Point2f(2416.f, 96.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2432.f, 96.f)));
	AddGameItem(new CoinPickup(Point2f(2432.f, 96.f)));


	AddGameItem(new BlueDecorBlock(Point2f(2768.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(2768.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2784.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(2784.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2800.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(2800.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2816.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(2816.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2832.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(2832.f, 128.f)));
	AddGameItem(new BlueDecorBlock(Point2f(2848.f, 128.f)));
	AddGameItem(new CoinPickup(Point2f(2848.f, 128.f)));

	AddGameItem(new ConcreteBlock(Point2f(3088.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3104.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3088.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3104.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3120.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3088.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3104.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3120.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3136.f, 32.f)));


	AddGameItem(new ConcreteBlock(Point2f(3328.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3344.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3360.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3376.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3392.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3408.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 32.f)));
	AddGameItem(new ConcreteBlock(Point2f(3344.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3360.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3376.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3392.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3408.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 48.f)));
	AddGameItem(new ConcreteBlock(Point2f(3360.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3376.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3392.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3408.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 64.f)));
	AddGameItem(new ConcreteBlock(Point2f(3376.f, 80.f)));
	AddGameItem(new ConcreteBlock(Point2f(3392.f, 80.f)));
	AddGameItem(new ConcreteBlock(Point2f(3408.f, 80.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 80.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 80.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 80.f)));
	AddGameItem(new ConcreteBlock(Point2f(3392.f, 96.f)));
	AddGameItem(new ConcreteBlock(Point2f(3408.f, 96.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 96.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 96.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 96.f)));
	AddGameItem(new ConcreteBlock(Point2f(3408.f, 112.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 112.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 112.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 112.f)));
	AddGameItem(new ConcreteBlock(Point2f(3424.f, 128.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 128.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 128.f)));
	AddGameItem(new ConcreteBlock(Point2f(3440.f, 144.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 144.f)));
	AddGameItem(new ConcreteBlock(Point2f(3456.f, 160.f)));

	AddGameItem(new FlagPole(Point2f(3606.f, 44.f)));
	AddGameItem(new ConcreteBlock(Point2f(3600.f, 32.f)));


	AddLiveItem(new Fish(Point2f(324.f, -18.f)));
	AddLiveItem(new Fish(Point2f(384.f, -18.f)));
	AddLiveItem(new Fish(Point2f(414.f, -18.f)));
	AddLiveItem(new Fish(Point2f(444.f, -18.f)));
	AddLiveItem(new Fish(Point2f(494.f, -18.f)));
	AddLiveItem(new Fish(Point2f(294.f, -18.f)));

	AddLiveItem(new Fish(Point2f(524.f, -18.f)));
	AddLiveItem(new Fish(Point2f(574.f, -18.f)));
	AddLiveItem(new Fish(Point2f(614.f, -18.f)));
	AddLiveItem(new Fish(Point2f(644.f, -18.f)));
	AddLiveItem(new Fish(Point2f(694.f, -18.f)));
	AddLiveItem(new Fish(Point2f(714.f, -18.f)));
	  
	AddLiveItem(new Fish(Point2f(784.f, -18.f)));
	
	AddLiveItem(new Fish(Point2f(824.f, -18.f)));
	AddLiveItem(new Fish(Point2f(874.f, -18.f)));
	AddLiveItem(new Fish(Point2f(914.f, -18.f)));
	AddLiveItem(new Fish(Point2f(944.f, -18.f)));
	AddLiveItem(new Fish(Point2f(994.f, -18.f)));

	AddLiveItem(new Fish(Point2f(1024.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1064.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1114.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1144.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1194.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1214.f, -16.f)));

	AddLiveItem(new Fish(Point2f(1294.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1334.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1394.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1434.f, -16.f)));

	AddLiveItem(new Fish(Point2f(1494.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1544.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1570.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1634.f, -16.f)));

	AddLiveItem(new Fish(Point2f(1694.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1734.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1794.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1834.f, -16.f)));
	
	AddLiveItem(new Fish(Point2f(1894.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1934.f, -16.f)));
	AddLiveItem(new Fish(Point2f(1984.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2034.f, -16.f)));

	AddLiveItem(new Fish(Point2f(2094.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2134.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2174.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2234.f, -16.f)));

	AddLiveItem(new Fish(Point2f(2294.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2334.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2394.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2434.f, -16.f)));

	AddLiveItem(new Fish(Point2f(2494.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2534.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2594.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2634.f, -16.f)));

	AddLiveItem(new Fish(Point2f(2694.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2734.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2794.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2834.f, -16.f)));

	AddLiveItem(new Fish(Point2f(2694.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2734.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2804.f, -16.f)));
	AddLiveItem(new Fish(Point2f(2834.f, -16.f)));
}

void Level2::ResetLevel() {
	DestroyAllItems();
	SetupLevel();
}

void Level2::DrawForeground() const {

}