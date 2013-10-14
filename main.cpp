#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

RenderWindow 	app(VideoMode(800,600), "test");
Event 			event;
int main()
{
	Font 			font;
					font.loadFromFile("VT323-Regular.ttf");
	vector<Text>	texts;
	Text* 			text = new Text;
					text->setFont(font);
					text->setPosition(Vector2f(0, 20*texts.size()));
					texts.push_back(*text);
	sf::String 	text_string;
	
	while(app.isOpen())
	{
		if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			app.close();
		}
		while(app.pollEvent(event))
		{
			if(event.type == Event::Closed) {
				app.close();
			}
			if(event.type == Event::TextEntered) {
				if(texts[texts.size()-1].getLocalBounds().width >= 790 && event.text.unicode != 8) {
							text = new Text;
							text->setFont(font);
							text->setPosition(Vector2f(0, 20*texts.size()));
					texts.push_back(*text);
					text_string.clear();
				}
				if(event.text.unicode == 8 && text_string.getSize() != 0) {
					text_string.erase(text_string.getSize()-1);
					if(text_string.getSize() == 0 && texts.size() != 0) {
						texts.erase(texts.begin()+texts.size()-1);
						text_string = texts[texts.size()-1].getString();
					}
				} else if(event.text.unicode != 8){
					text_string += event.text.unicode;
				}
				texts[texts.size()-1].setString(text_string);
			}
		}

		app.clear();
		for(int i=0; i<texts.size(); i++) {
			app.draw(texts[i]);
		}
		app.display();
	}
}
