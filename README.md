+		this	0x0000019c3afb3ae0 {...}	Level * {Level1}


# TODO:

NU:

2. Goomba's toevoegen nadat we een schietmannetje zijn
3. Kunnen winnen (vlag nemen)!

DAN:

0. Presentatie

1. m_p bij pointer

2. LiveItem protected member variables moeten protected member functions worden (getters and setters)

3. virtuele methodes in GameItem die geen implementatie hebben mogen weg

4. Hernoem CollisionLocation items, moet zijn 

	enum class CollisionLocation {
		liveItemBumpsOnTheRight,
		liveItemBumpsOnTheLeft,
		liveItemBumpsFromTheBottom,
		liveItemBumpsFromTheTop,
		liveItemBumpsOnTheLeftTop,
		noCollision
	};

	static CollisionLocation determineCollisionDir(Rectf liveItemRect, Vector2f RichtingLiveItem, Rectf itemRect);

5. Als LivceItem positie x < 0 dan setActive(false)

LATER:
1. 
-> 			Rectf src{ GetSpriteClipWidth() * (m_AnimStartFrameX), GetSpriteClipHeight() * (m_AnimStartFrameY + 1),sourceWidth,sourceHeight };
	Y begint bij 0, niet 1. Zou overal aangepast moeten worden
	
2. rename UpdateGameItem naam UpdateItem

3. Mushroom beweegt

4. Camera automatic zoom in/out

5. Parallax background effect: ?

6. Camera transition

7. QuestonBlock zou de verassing als parameter kunnen meekrijgen en die dan bij activatie toevoegen aan de level ipv bij de start

	AddGameItem(new QuestionBlock(Point2f(336.f, 320.f)));
	AddGameItem(new Coin(Point2f(368.f, 320.f)));


7. In Pipe gaan

8. Ster -> onoverwinnelijk

9. Naar beneden crashen (gehurkt springen)

10. In de lucht niet mogelijk om te draaien

# Presentatie

1. Camera

De camera volgt mario

Free moving area: Ik kan mannetje bewegen zonder dat de camera beweegt. Als ik meer beweeg dan volgt de camera

Ease in/out: Als ik blijf drukken met de toets dan versnelt het mannetje 

Oorspronkelijke mario bros heeft geen parallax en ik denk ook geen zoom in/out

De camera gaat nooit buiten de bounderies

De camera jumps to different room

2. Animations

De vlag
Springen een normaal blokje ->
Springen een question blokje -> botst omhoog -> komt een verassing uit die ik kan nemen

Ik kan tegen normale blokjes springen. Als klein mannetje duw je dan de blokjes omhoog. Als groot mannetje
maak je het blokje kapot. Dus hier ik spring ik als klein mannetje tegen een blokje.

Net zoals in het oorspronkelijke spel heb ik verschillende Q-blokjes. Sommige Q-blokjes geven een muntje 
als verassing. Sommige Q-blokjes zijn zoals het tweede en vijfde blokje. Deze 2 blokjes zijn precies dezelfe
en de verassing hangt af van het type mannetje dat er tegenaan springt. Nl
als een klein mannetje ertegen springt, dan komt er een mushroom uit. Als een groot mannete ertegen springt
dan komt er een bloem uit. En dus dat demonstreer ik hier. 

Zoals ik zei eerder, een gewoon blokje wordt vernietigd met mannetje. Dat demonstreer ik nu, nu ik een groot mannetje ben.

Als ik een musroom of bloem oppak, dan verdwijnt die animatie (dying animation)

Op het einde van het spel grijp ik naar de vlag die naar beneden valt.

3. Interactions

Schieten van enemie

4. Game implementation

Complicated gameplay

5. Quality of code




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

