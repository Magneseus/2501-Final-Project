#pragma once

#include <functional>

#include "SFML\Graphics.hpp"
#include "GameObject.h"

class UI : public Drawable {
public:
	UI();
	~UI();

	class Button {
	public:
		Button(float x, float y, float w, float h, sf::String text, std::function<void()> callback);
		~Button();

		std::function<void()> function;
		vec::Vector2 position;
		vec::Vector2 size;

		sf::RectangleShape body;
		sf::Text label;

		bool isClicked(float x, float y);
		void execute();
	};

	std::vector<Button*> buttons;

	void addButton(float x, float y, float w, float h, sf::String _text, std::function<void()> callback);

	bool processClick(float clickX, float clickY);

	void print();
	//static UI* mainMenu();

private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};