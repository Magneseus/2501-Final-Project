#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Dependency Test");

	sf::CircleShape circ(400);
	circ.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape)
				window.close();
		}

		window.clear();
		window.draw(circ);
		window.display();
	}

	return 0;
}