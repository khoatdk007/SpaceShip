#ifndef _UFO_H
#define _UFO_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Ufo {
private:
	sf::RenderWindow *window;
	sf::Texture ufoTexture;
	sf::Sprite ufo;
public:
	Ufo(sf::RenderWindow *window, sf::Texture &ufoTexture, sf::Clock clock);
	void update();
	void draw();
	sf::Vector2f getPosition();
	bool isKilled(Bullet bullet);
	bool isOutScreen();
	bool isAttacking(SpaceShip spaceShip);
};
#endif