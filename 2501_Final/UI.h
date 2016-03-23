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

	class TextBox {
	public:
		TextBox(float x, float y, float w, float h, sf::String _text, int fontSize);
		~TextBox();

		vec::Vector2 position;
		vec::Vector2 size;

		sf::Text text;
	};

	std::vector<Button*> buttons;
	std::vector<TextBox*> textboxes;

	void addButton(float x, float y, float w, float h, sf::String _text, std::function<void()> callback);
	void addTextBox(float x, float y, float w, float h, sf::String _text, int fontSize);

	bool processClick(float clickX, float clickY);
	
	void clear();
	void print();

private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};