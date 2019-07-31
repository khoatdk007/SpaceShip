#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
	sf::RenderWindow *window;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;
	double speed, frame;
public:
	Animation(sf::RenderWindow *window, sf::Texture &texture, sf::Vector2f position, unsigned int width, unsigned int height, double speed, double scale);
	void update();
	void draw();
	bool isEnded();
};

#endif