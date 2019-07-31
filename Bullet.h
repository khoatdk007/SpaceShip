#ifndef _BULLET_H
#define _BULLET_H

#include <SFML/Graphics.hpp>
#include "SpaceShip.h"

class Bullet {
private:
	sf::RenderWindow *window;
	sf::Sprite bullet;
	double startPosition;
public:
	Bullet(sf::RenderWindow *window, SpaceShip spaceShip, sf::Texture &bulletTexture);
	void update();
	void draw();
	bool isOver();
	sf::Vector2f getPosition();
};

#endif
