
#include "UI.h"

UI::UI() {
}

UI::~UI() {}

UI::Button::Button(float x, float y, float w, float h, sf::String text, std::function<void()> callback) {
	// TODO: Make button auto size to text size? 
	
	position = vec::Vector2(x, y);
	size = vec::Vector2(w, h);

	function = callback;

	body.setPosition(x, y);
	body.setSize(sf::Vector2f(w, h));
	body.setOutlineColor(sf::Color::Blue);
	body.setOutlineThickness(3);
	body.setFillColor(sf::Color::White);

	label.setString(text);
	label.setFont(Global::niceFont);
	label.setCharacterSize(20);
	label.setColor(sf::Color::Blue);

	sf::FloatRect rect = label.getLocalBounds();

	label.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	label.setPosition(x + w / 2, y + h / 2);
}

UI::Button::~Button() {}

void UI::addButton(float x, float y, float w, float h, sf::String _text, std::function<void()> callback) {
	Button* b = new Button(x, y, w, h, _text, callback);
	buttons.push_back(b);
}

void UI::print() {
	std::cout << "hello i am a callback" << std::endl;
}

bool UI::processClick(float clickX, float clickY) {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isClicked(clickX, clickY)) {
			buttons[i]->execute();
			return true;
		}
	}
	return false;
}

void UI::draw(sf::RenderTarget& w, sf::RenderStates s) const {
	Button* b;

	for (int i = 0; i < buttons.size(); i++) {
		b = buttons[i];
		w.draw(b->body, s);
		w.draw(b->label, s);
	}
}

bool UI::Button::isClicked(float x, float y) {
	return (x > position.getX() && y > position.getY() &&
		x < position.getX() + size.getX() && y < position.getY() + size.getY());
}

void UI::Button::execute() { function(); }