https://www.myinstants.com/en/search/?name=mario
# TODO

- reset game als je dood gaat

## Bugs




## Feedback

- Feedback van leerkracht verwerken *****

## Grading rubric

### Camera +



- Parallax background effect -> 2 background, 1 met wolken, 1 met boompjes **

- Ease in/out camera moving speed.??? 

- Camera automatic zoom in/out -> in en uitzoom bij start level en einde level?

### Animations ++

### Interaction player and props, enemies, level, equipment +++

- Transfer ownership of one object to another -> mogelijk in dit spel??

### Game implementation (how much is there) ++++



- Mushroom powerup beweegt ***

- 2de level **

- Ster -> onoverwinnelijk

- Naar beneden crashen (gehurkt springen)

- In de lucht niet mogelijk om te draaien

### HUD and UI (heads up and user interface) ++



- Game settings, zoals sounds on/off, verhogen, ... *****

### Sound +



- Some actions have a sounds representation *****

- Many actions in the game have a sound representation that is played / canceled when necessary. *****
 
- The volume can be adjusted/turned on/off using keypresses. *****

### Exceeds standards

- Level editor ... <- Doenbaar
- load level from a file <- Doenbaar
- Animation system based on data from a file.
- load/save game system
- Bone animation
- Pathfinding
- A.I.
- Inventory system.
- Particle system
- Level generation
- others..

##Details

- Als je doodvalt en er zijn obstakels, dan bots je daartegen

##Code

- LiveItem protected member variables moeten protected member functions worden (getters and setters)

- virtuele methodes in GameItem die geen implementatie hebben mogen weg

- Hernoem CollisionLocation items, moet zijn 

	enum class CollisionLocation {
		liveItemBumpsOnTheRight,
		liveItemBumpsOnTheLeft,
		liveItemBumpsFromTheBottom,
		liveItemBumpsFromTheTop,
		liveItemBumpsOnTheLeftTop,
		noCollision
	};

	static CollisionLocation determineCollisionDir(Rectf liveItemRect, Vector2f RichtingLiveItem, Rectf itemRect);

- Als LivceItem positie x < 0 dan setActive(false)

- Rectf src{ GetSpriteClipWidth() * (m_AnimStartFrameX), GetSpriteClipHeight() * (m_AnimStartFrameY + 1),sourceWidth,sourceHeight };
	Y begint bij 0, niet 1. Zou overal aangepast moeten worden

- rename UpdateGameItem naam UpdateItem

- QuestonBlock zou de verassing als parameter kunnen meekrijgen en die dan bij activatie toevoegen aan de level ipv bij de start

	AddGameItem(new QuestionBlock(Point2f(336.f, 320.f)));
	AddGameItem(new Coin(Point2f(368.f, 320.f)));

TODOs

- checkpoint en als sterft terug naar checkpoint

# NOTITIES


void functie1(std::string string1) {
	string1 = "b";
}

void functie2(std::string& string2) {
	string2 = "c";
}

void functie2b(const std::string& string2b) {
	// string2b = "c"; -> kan niet, is const
}

void functie3(std::string* string3) {
	*string3 = "d";
}

void functie4(std::string string1) {
	string1.append("x");
}

void functie5(std::string& string2) {
	string2.append("y");
}

void functie5b(const std::string& string2b) {
	// hiet op string2b kan ik ENKEL methods van string2b oproepen die const zijn gedeclareerd
	int i = string2b.length();	// dit kan
	// string2b.append("y");	// kan niet omdat append niet const is
}

void functie6(std::string* string3) {
	string3->append("z");
}

void test() {
	{
		std::string eenString = "AAAA";
		functie1(eenString);	// maakt een copy en bij terugkomst is eenString de oorspronkelijke, output is dus AAAA
		std::cout << eenString << std::endl;
	}
	{
		std::string eenString = "AAAA";
		functie2(eenString);	// gebruikt een referntie, dus geen copy en oorsprongkelijke kan gewijzigd worden, ouput is dus c
		std::cout << eenString << std::endl;
	}
	{
		std::string eenString = "AAAA";
		functie2b(eenString);	// gebruikt een referentie, maar is const en dus kan de method zelf niks wijzigen (zie implementatie functie2b doet nu niks), output is dus AAAA
		std::cout << eenString << std::endl;
	}
	{
		std::string eenString = "AAAA";
		functie3(&eenString);	// gebruikt een pointer door een pointer van een object te nemen, en dus kan gewijzigd worden, output is dus d
		std::cout << eenString << std::endl;
	}
	{
		std::string* eenString = new std::string("AAAA");
		functie3(eenString);	// gebruikt een pointer maar op een andere manier (was al een pointer), en kan dus gewijzigd worden, output is dus d
		std::cout << *eenString << std::endl;
	}
	{
		std::string eenString = "AAAA";
		functie4(eenString);	// gebruikt een copy, en dus zelf door methods op te roepen in dat object het heeft geen invloed op het object
		std::cout << eenString << std::endl;
	}
	{
		std::string eenString = "AAAA";
		functie5(eenString);	// gebruikt een referentie, maar is const en dus kan de method zelf niks wijzigen (zie implementatie functie2b doet nu niks), output is dus AAAA
		std::cout << eenString << std::endl;
	}
	{
		std::string eenString = "AAAA";
		functie6(&eenString);	// ebruikt een pointer en dus kan dus wijzigen. Output is dus AAAAz
		std::cout << eenString << std::endl;
	}
}

