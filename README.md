# TODO:

NU:
1. Vlag op einde plaatsen

2. Eerste Q -> ALTIJD een coin

3. Tweede Q -> mushroom bij klein mannetje, flower bij groot mannetje

4. Mushroom -> Switch naar groot mannetje

5. Flower -> Switch naar flower mannetje

6. Derde en 4de Q -> coins

7. 5de Q -> mushroom bij klein mannetje, flower bij groot mannetje

8. Kunnen sterven!

9. Kunnen winnen (vlag nemen)!

EN TESTEN

DAN:

0. Presentatie

1. m_p bij pointer

2. LiveItem protected member variables moeten protected member functions worden (getters and setters)

3. Delete LiveItems in Level (crasht)

4. Bibber

5. virtuele methodes in GameItem die geen implementatie hebben mogen weg

6. Hernoem CollisionLocation items, moet zijn 

	enum class CollisionLocation {
		liveItemBumpsOnTheRight,
		liveItemBumpsOnTheLeft,
		liveItemBumpsFromTheBottom,
		liveItemBumpsFromTheTop,
		liveItemBumpsOnTheLeftTop,
		noCollision
	};

	static CollisionLocation determineCollisionDir(Rectf liveItemRect, Vector2f RichtingLiveItem, Rectf itemRect);

7. Als LivceItem positie x < 0 dan setActive(false)

LATER:
1. 
-> 			Rectf src{ GetSpriteClipWidth() * (m_AnimStartFrameX), GetSpriteClipHeight() * (m_AnimStartFrameY + 1),sourceWidth,sourceHeight };
	Y begint bij 0, niet 1. Zou overal aangepast moeten worden
	
2. rename UpdateGameItem naam UpdateItem

3. Mushroom beweegt

4. Camera automatic zoom in/out

5. Parallax background effect: ?

6. Camera transition

7. In Pipe gaan

8. Ster -> onoverwinnelijk

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


