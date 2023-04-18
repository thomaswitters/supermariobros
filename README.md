#TODO

1. NU: m_p bij pointer

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

6. 
-> 			Rectf src{ GetSpriteClipWidth() * (m_AnimStartFrameX), GetSpriteClipHeight() * (m_AnimStartFrameY + 1),sourceWidth,sourceHeight };
	Y begint bij 0, niet 1. Zou overal aangepast moeten worden
	
7. rename UpdateGameItem naam UpdateItem

8. Mushroom beweegt

9. Camera automatic zoom in/out

10. Parallax background effect: ?

11. Camera transition

12. QuestonBlock zou de verassing als parameter kunnen meekrijgen en die dan bij activatie toevoegen aan de level ipv bij de start

	AddGameItem(new QuestionBlock(Point2f(336.f, 320.f)));
	AddGameItem(new Coin(Point2f(368.f, 320.f)));

13. In Pipe gaan

14. Ster -> onoverwinnelijk

15. Naar beneden crashen (gehurkt springen)

16. In de lucht niet mogelijk om te draaien


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

