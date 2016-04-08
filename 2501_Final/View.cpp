#include "View.h"

#include <iostream>

View::View(Model* m)
	: model(m),
	WINDOW_WIDTH(1600),
	WINDOW_HEIGHT(1000),
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Protectors"),
	showFPS(true),
	renderablesSpawned(false)
{
	// Set the middle of the screen
	Global::middleWindowCoords = sf::Vector2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	// Load some fonts
	if (!Global::niceFont.loadFromFile("fonts/FiraSans-Regular.otf"))
	{
		std::cout << "Nice font not loaded!\n";
	}
	fpsText.setFont(Global::niceFont);
	mCoordsText.setFont(Global::niceFont);

	menu = new UI();

	HUDTexture.loadFromFile("img/HUD.png");
	HUD.setTexture(HUDTexture);
	HUD.setPosition(0, WINDOW_HEIGHT - HUDTexture.getSize().y);

	compassBaseTex.loadFromFile("img/compass_base.png");
	compassBase.setTexture(compassBaseTex);
	compassBase.setPosition(75, WINDOW_HEIGHT - HUDTexture.getSize().y+15);
	
	compassNeedleTex.loadFromFile("img/compass_needle.png");
	compassNeedle.setTexture(compassNeedleTex);
	compassNeedle.setPosition(compassBase.getPosition().x + compassNeedleTex.getSize().x / 2, 
		WINDOW_HEIGHT - HUDTexture.getSize().y + 15 + compassNeedleTex.getSize().y / 2);
	compassNeedle.setOrigin(compassNeedleTex.getSize().x/2, compassNeedleTex.getSize().y/2);

	equippedWeapon.setFont(Global::niceFont);
	equippedWeapon.setColor(sf::Color::Black);
	equippedWeapon.setCharacterSize(18);
	equippedWeapon.setPosition(25, WINDOW_HEIGHT - HUDTexture.getSize().y + 30);

	holsteredWeapon.setFont(Global::niceFont);
	holsteredWeapon.setColor(sf::Color::Black);
	holsteredWeapon.setCharacterSize(12);
	holsteredWeapon.setPosition(40, WINDOW_HEIGHT - HUDTexture.getSize().y + 60);

	window.setKeyRepeatEnabled(false);	// prevent player from spamming keys accidentally
}

View::~View()
{
	delete menu;
}

void View::render()
{
	window.clear();

	// Some debugging zoom capabilities
	if (Global::DEBUG && Global::INFOCUS)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
		{
			Global::ZOOM += 0.1f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
		{
			Global::ZOOM -= 0.1f;
		}
	}

	// Zoom the screen in/out
	sf::View zoomView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	zoomView.zoom(Global::ZOOM);
	window.setView(zoomView);

	if (renderablesSpawned)
	{
		vec::Vector2 ppos = globalTransform.transformPoint(sf::Vector2f(0, 0));
		ppos *= -0.1f;

		background.setPosition(ppos.getSfVec());
		window.draw(background, globalTransform);

		window.draw(hangar, globalTransform);
		window.draw(enemyHangar, globalTransform);
	}

	for (auto it = drawables.begin(); it != drawables.end(); )
	{
		// Check if it needs to be removed
		if ((*it)->removeFunc())
		{
			(*it)->andType(0b101);
			it = drawables.erase(it);
		}
		else
		{
			if (*it != NULL)
			{
				vec::Vector2 rPos = (*it)->getPosition();
				vec::Vector2 gPos = vec::Vector2(globalTransform.transformPoint(sf::Vector2f(0, 0)));
				gPos *= -1;

				if (gPos.dist(rPos) < WINDOW_WIDTH * 2)
				{
					(*it)->debugDraw(window, globalTransform);
					window.draw(**it, globalTransform);
				}
			}
			++it;
		}

	}

	if (Global::DEBUG)
	{
		// DEBUG
		for (auto it = Debug::debugDrawables.begin(); it != Debug::debugDrawables.end(); ++it)
		{
			window.draw(**it, globalTransform);
			delete *it;
		}
		Debug::debugDrawables.clear();
	}



	//   UI STUFF
	
	// Reset window to normal
	window.setView(window.getDefaultView());

	if (Global::DEBUG)
	{
		// display FPS
		if (showFPS)
		{
			float total = 0;
			for (auto it = fps.begin(); it != fps.end(); ++it)
				total += *it;

			total /= fps.size();

			int FPS = 1.0f / total;
			std::stringstream fpsString;
			fpsString << "FPS: " << FPS;

			fpsText.setString(fpsString.str());
			fpsText.setCharacterSize(20);
			fpsText.setColor(sf::Color::White);
			fpsText.setPosition(sf::Vector2f(2, 2));
			window.draw(fpsText);
		}

		// Display co-ordinates
		sf::Vector2f worldPosf;
		worldPosf += vec::Vector2(Global::mouseWindowCoords).operator*=(-1).getSfVec();
		worldPosf = globalTransform.transformPoint(worldPosf);
		worldPosf.x *= -1;

		worldPosf.x -= std::fmodf(worldPosf.x, 1);
		worldPosf.y -= std::fmodf(worldPosf.y, 1);

		std::stringstream mString;
		mString << "X:" << worldPosf.x << "  " << "Y: " << worldPosf.y;

		mCoordsText.setString(mString.str());
		mCoordsText.setCharacterSize(20);
		mCoordsText.setColor(sf::Color::White);
		mCoordsText.setPosition(sf::Vector2f(2, window.getSize().y - 22));
		window.draw(mCoordsText);
	}
	
	// UI stuff
	window.draw(*menu);

	if (Global::getState() != -1) drawHUD();

	window.display();
}

/*
	This function simply adds a drawable object to the list to be rendered.
*/
void View::addDrawable(Drawable* d, bool addBack)
{
	// If we have a null pointer, don't add it to the list
	if (!d) return;

	if (!addBack)
		drawables.push_back(d);
	else
		drawables.insert(drawables.begin(), d);
}

/*
	This function removes a drawable object from our render list.

	Return:
	 - true: The object was stored in our list, and was flagged to be removed
	 - false: The object wasn't stored in our list, not flagged for removal
*/
bool View::delDrawable(Drawable* d)
{
	bool contains = false;
	for (auto it = drawables.begin(); it != drawables.end() && !contains; it++)
	{
		// Object was found
		if (*it == d)
		{
			contains = true;
			break;
		}
	}

	// If we have a pointer to the object stored, "delete" it
	if (contains)
	{
		d->deleteObject();
		d->andType(0b101);
	}

	// Tell them if we had an object stored and flagged it
	return contains;
}

bool View::remDrawable(Drawable* u)
{
	for (auto it = drawables.begin(); it != drawables.end(); it++)
	{
		// Object was found
		if (*it == u)
		{
			drawables.erase(it);
			return true;
		}
	}

	return false;
}

/*
	This function sets the global transform object. Will be applied to all Drawables.
*/
void View::setTransform(const sf::Transform& _trans)
{
	globalTransform = _trans;
}

/*
	Return transforms.
*/
sf::Transform View::getTransform()
{
	return globalTransform;
}

void View::addFPS(const sf::Time& timeForFrame)
{
	fps.push_back(timeForFrame.asSeconds());

	if (fps.size() > 20)
		fps.pop_front();
}

void View::spawnRenderables()
{
	// Background img
	backgroundTex.loadFromFile("img/space.jpg");
	backgroundTex.setRepeated(true);

	background.setTexture(backgroundTex);
	background.setTextureRect(sf::IntRect(-10000, -10000, 10000, 10000));

	background.setOrigin(sf::Vector2f(backgroundTex.getSize().x/2, backgroundTex.getSize().y/2));
	background.setScale(1.5, 1.5);
	background.setPosition(-400, -1000);


	renderablesSpawned = true;
}

void View::drawHUD() {

	Entity* e = Global::player;
	window.draw(HUD);

	Player* p = dynamic_cast<Player*>(e);
	
	if (p->vehicle != NULL) {
		window.draw(compassBase);

		vec::Vector2 toObjective(Global::objective);
		toObjective -= p->position;

		compassNeedle.setRotation(toDegrees(toObjective.heading()));

		window.draw(compassNeedle);
	} else {
		sf::String mainWeapon;
		sf::String holstered;

		if (p->currentLoadout) {
			mainWeapon = "Current: " + p->currentWeapon->getName().toAnsiString();
			holstered = "Holstered: " + p->getOtherWeapon()->getName().toAnsiString();
		}

		equippedWeapon.setString(mainWeapon);
		holsteredWeapon.setString(holstered);

		window.draw(equippedWeapon);
		window.draw(holsteredWeapon);
	}

	sf::RectangleShape barOut;
	barOut.setSize(sf::Vector2f(200, 10));
	barOut.setPosition(window.getSize().x/2-100, window.getSize().y - 20);
	barOut.setOutlineColor(sf::Color::Black);
	barOut.setOutlineThickness(2);
	sf::Color grey = sf::Color::Black;
	grey.r += 100;
	grey.g += 100;
	grey.b += 100;
	barOut.setFillColor(grey);

	sf::RectangleShape barIn(barOut);
	barIn.setSize(sf::Vector2f(barOut.getSize().x * (p->curHealth / p->maxHealth), barOut.getSize().y));
	barIn.setFillColor(sf::Color::Red);
	barIn.setOutlineThickness(0);

	window.draw(barOut);
	window.draw(barIn);
}
