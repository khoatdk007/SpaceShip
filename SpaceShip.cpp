#include "SpaceShip.h"

SpaceShip::SpaceShip(sf::RenderWindow *window) {
	this->window = window;
	this->shipTexture.loadFromFile("Resource/Img/ship.png");
	this->shipTexture.setSmooth(true);
	this->ship.setTexture(this->shipTexture);
	this->ship.setOrigin(sf::Vector2f(this->ship.getTexture()->getSize().x / 2, this->ship.getTexture()->getSize().y / 2));
	this->ship.setPosition(sf::Vector2f(ScreenWidth / 2, ScreenHeight - this->ship.getTexture()->getSize().y / 2));
	this->skills.push_back(Skill(0.2, 2));
	this->skills.push_back(Skill(1.5, 5));
	this->hp = maxHp;
	this->ki = maxKi;
	this->currentSkill = 1;
}
void SpaceShip::update() {
	sf::Vector2f shipPosition = this->ship.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		shipPosition.x -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		shipPosition.x += 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		shipPosition.y -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		shipPosition.y += 5;

	if (shipPosition.x <= this->ship.getTexture()->getSize().x / 2)
		shipPosition.x = this->ship.getTexture()->getSize().x / 2;
	if (shipPosition.x >= ScreenWidth - this->ship.getTexture()->getSize().x / 2)
		shipPosition.x = ScreenWidth - this->ship.getTexture()->getSize().x / 2;
	if (shipPosition.y <= this->ship.getTexture()->getSize().y / 2)
		shipPosition.y = this->ship.getTexture()->getSize().y / 2;
	if (shipPosition.y >= ScreenHeight - this->ship.getTexture()->getSize().y / 2)
		shipPosition.y = ScreenHeight - this->ship.getTexture()->getSize().y / 2;

	this->ship.setPosition(shipPosition);

}
void SpaceShip::draw() {
	this->window->draw(this->ship);
}

sf::Vector2f SpaceShip::getPosition() {
	return this->ship.getPosition();
}

sf::Vector2u SpaceShip::getSize() {
	return this->shipTexture.getSize();
}

void SpaceShip::skillsUpdate(double timeUpdate) {
	for (int i = 0; i < this->skills.size(); i++) {
		this->skills.at(i).update(timeUpdate);
	}
}

Skill SpaceShip::getSkill(unsigned short skill) {
	return this->skills.at(skill % (this->skills.size() + 1) - 1);
}

bool SpaceShip::skillAvailable(unsigned short skill) {
	return (this->getSkill(skill).isAvailable() && (this->ki >= this->getSkill(skill).getKiToUse()));
}

void SpaceShip::useSkill(unsigned short skill) {
	this->skills.at(skill - 1).use();
	this->ki -= this->getSkill(skill).getKiToUse();
	if (this->ki < 0) this->ki = 0;
}

void SpaceShip::addKi(double newKi) {
	this->ki += newKi * 5;
	if (this->ki > maxKi) this->ki = maxKi;
}

double SpaceShip::getPercentKi() {
	return this->ki / maxKi;
}

double SpaceShip::getPercentHp() {
	return this->hp / maxHp;
}

bool SpaceShip::isDead() {
	return this->hp <= 0;
}

void SpaceShip::downHp() {
	this->hp -= maxHp / 4;
	if (this->hp < 0) this->hp = 0;
}

void SpaceShip::upHp() {
	this->hp += maxHp / 5;
	if (this->hp > maxHp) this->hp = maxHp;
}


