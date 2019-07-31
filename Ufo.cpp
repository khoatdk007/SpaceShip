#include "Ufo.h"

Ufo::Ufo(sf::RenderWindow *window, sf::Texture &ufoTexture, sf::Clock clock) {
	this->window = window;
	srand(time(NULL));
	this->ufoTexture = ufoTexture;
	this->ufo.setTexture(ufoTexture);
	this->ufo.setOrigin(this->ufoTexture.getSize().x / 2, this->ufoTexture.getSize().y / 2);
	this->ufo.setPosition(sf::Vector2f(clock.getElapsedTime().asMicroseconds() % (ScreenWidth - this->ufoTexture.getSize().x) + this->ufoTexture.getSize().x / 2, -100));
}
void Ufo::update() {
	this->ufo.move(sf::Vector2f(0.f, 2.f));
}
void Ufo::draw() {
	this->window->draw(this->ufo);
}
sf::Vector2f Ufo::getPosition() {
	return this->ufo.getPosition();
}
bool Ufo::isKilled(Bullet bullet) {
	if ((bullet.getPosition().y < this->ufo.getPosition().y + this->ufoTexture.getSize().y / 4) &&
		(bullet.getPosition().y > this->ufo.getPosition().y - this->ufoTexture.getSize().y / 2) &&
		(bullet.getPosition().x > this->ufo.getPosition().x - this->ufoTexture.getSize().x / 2) &&
		(bullet.getPosition().x < this->ufo.getPosition().x + this->ufoTexture.getSize().x / 2)) {
		return true;
	}
	return false;
}
bool Ufo::isOutScreen() {
	return this->ufo.getPosition().y > ScreenHeight + ufoRadius;
}

bool Ufo::isAttacking(SpaceShip spaceShip) {
	double dx = spaceShip.getPosition().x - this->getPosition().x;
	double dy = spaceShip.getPosition().y - this->getPosition().y;
	double distance = std::sqrt(dx * dx + dy * dy);
	return distance <= shipRadius + ufoRadius;
}
