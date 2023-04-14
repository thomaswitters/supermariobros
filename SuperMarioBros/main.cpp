#include "pch.h"
#include <ctime>
#include "Game.h"


void StartHeapControl();
void DumpMemoryLeaks();

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
	size_t i = string2b.length();	// dit kan
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

int SDL_main(int argv, char** args)
{



	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();

	Game* pGame{ new Game{ Window{ "Project name - Name, first name - 1DAEXX", 380.f , 240.f } } };
	pGame->Run();
	delete pGame;

	DumpMemoryLeaks();
	return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}


