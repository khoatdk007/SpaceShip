#include "Animation.h"

Animation::Animation(sf::RenderWindow *window, sf::Texture &texture, sf::Vector2f position, unsigned int width, unsigned int height, double speed, double scale) {
	this->window = window;
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(width / 2, height / 2);
	for (int i = 0; i < static_cast<int>(texture.getSize().x / width); i++) {
		this->frames.push_back(sf::IntRect(width * i, 0, width, height));
	}
	this->frame = 0;
	this->speed = speed;
	this->sprite.setTextureRect(frames.at(0));
	this->sprite.setPosition(position);
	this->sprite.setScale(sf::Vector2f(scale, scale));
}
void Animation::update() {
	this->frame += this->speed;
	if (this->frame > this->frames.size() - 1) this->frame = this->frames.size() - 1;
	this->sprite.setTextureRect(frames.at(static_cast<int>(this->frame)));
}
void Animation::draw() {
	this->window->draw(this->sprite);
}
bool Animation::isEnded() {
	return this->frame + this->speed > this->frames.size() - 1;
}

