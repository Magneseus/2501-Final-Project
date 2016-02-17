#include "Controller.h"

Controller::Controller(Model* m, View* v)
	: model(m),
	view(v)
{
	
}

Controller::~Controller()
{
	
}

void Controller::input()
{
	// EVENT-BASED INPUT
	sf::Event e;
	while (view->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyReleased:
			if (e.key.code == sf::Keyboard::Escape)
				view->window.close();
			break;
		case sf::Event::Closed:
			view->window.close();
			break;
		}
	}

	// REAL-TIME INPUT

}