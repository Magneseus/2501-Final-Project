
#include "UI.h"
#include "Game.h"

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
	sf::Color fill = sf::Color::Cyan;
	//fill.a = 100;
	body.setFillColor(fill);

	body.setOrigin(w / 2, h / 2);

	label.setString(text);
	label.setFont(Global::niceFont);
	label.setCharacterSize(20);
	label.setColor(sf::Color::Blue);

	sf::FloatRect rect = label.getLocalBounds();

	label.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	label.setPosition(x, y);
}

UI::Button::~Button() {}

UI::TextBox::TextBox(float x, float y, float w, float h, sf::String _text, int fontSize) {
	position = vec::Vector2(x, y);
	size = vec::Vector2(w, h);

	text.setString(_text);
	text.setFont(Global::niceFont);
	text.setCharacterSize(fontSize);
	text.setColor(sf::Color::White);

	sf::FloatRect rect = text.getLocalBounds();

	text.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	text.setPosition(x + w / 2, y + h / 2);
}

UI::TextBox::~TextBox() {}

void UI::addButton(float x, float y, float w, float h, sf::String _text, std::function<void()> callback) {
	Button* b = new Button(x, y, w, h, _text, callback);
	buttons.push_back(b);
}

void UI::addTextBox(float x, float y, float w, float h, sf::String _text, int fontSize) {
	TextBox* b = new TextBox(x, y, w, h, _text, fontSize);
	textboxes.push_back(b);
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

void UI::clear() {
	buttons.clear();
	textboxes.clear();
}

int UI::getState() { return state; }

void UI::setState(int in) { state = in; }

void UI::draw(sf::RenderTarget& w, sf::RenderStates s) const {
	Button* b;

	for (int i = 0; i < buttons.size(); i++) {
		b = buttons[i];
		w.draw(b->body, s);
		w.draw(b->label, s);
	}

	for (int i = 0; i < textboxes.size(); i++) {
		w.draw(textboxes[i]->text);
	}
}

bool UI::Button::isClicked(float x, float y) {
	return (x > position.getX() - size.getX()/2 &&
		y > position.getY() - size.getY()/2 &&
		x < position.getX() + size.getX()/2 &&
		y < position.getY() + size.getY()/2);
}

void UI::Button::execute() { function(); }
