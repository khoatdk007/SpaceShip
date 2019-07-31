#include "Bullet.h"

Bullet::Bullet(sf::RenderWindow *window, SpaceShip spaceShip, sf::Texture &bulletTexture) {
	this->window = window;
	this->bullet.setTexture(bulletTexture);
	this->bullet.setOrigin(sf::Vector2f(bulletTexture.getSize().x / 2, bulletTexture.getSize().y / 2));
	this->bullet.setPosition(spaceShip.getPosition().x, spaceShip.getPosition().y - spaceShip.getSize().y / 10 * 3);
	this->startPosition = spaceShip.getPosition().y;
}
void Bullet::update() {
	this->bullet.setPosition(sf::Vector2f(this->bullet.getPosition().x, this->bullet.getPosition().y - 20));
}
void Bullet::draw() {
	this->window->draw(this->bullet);
}
bool Bullet::isOver() {
	return this->getPosition().y < 0;
}
sf::Vector2f Bullet::getPosition() {
	return this->bullet.getPosition();
}