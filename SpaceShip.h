#ifndef _SPACESHIP_H
#define _SPACESHIP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Skill.h"
#include "Definition.h"

class SpaceShip {
private:
	sf::RenderWindow *window;
	sf::Texture shipTexture;
	sf::Sprite ship;
	double ki;
	double hp;
	std::vector<Skill> skills;
	unsigned short currentSkill;
public:
	SpaceShip(sf::RenderWindow *window);;
	void update();
	void draw();
	sf::Vector2f getPosition();
	sf::Vector2u getSize();
	void skillsUpdate(double timeUpdate);
	Skill getSkill(unsigned short skill);
	bool skillAvailable(unsigned short skill);
	void useSkill(unsigned short skill);
	void addKi(double newKi);
	double getPercentKi();
	double getPercentHp();
	bool isDead();
	void downHp();
	void upHp();
};

#endif