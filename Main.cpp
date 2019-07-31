#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "Ufo.h"
#include "Animation.h"
#include "Definition.h"

void MainGame(sf::RenderWindow &window) {

	sf::Texture background;
	background.loadFromFile("Resource/Img/bg.png");
	sf::Sprite bgSprite(background);

	sf::Texture bulletTexture;
	bulletTexture.loadFromFile("Resource/Img/bullet.png");
	bulletTexture.setSmooth(true);

	sf::Texture ufoTexture;
	ufoTexture.loadFromFile("Resource/Img/ufo.png");
	ufoTexture.setSmooth(true);

	sf::Texture ufoExplosion;
	ufoExplosion.loadFromFile("Resource/Img/Explosion/type_B.png");
	ufoExplosion.setSmooth(true);

	sf::Texture skill2;
	skill2.loadFromFile("Resource/Img/Explosion/type_C.png");
	skill2.setSmooth(true);

	sf::Texture shipAttacking;
	shipAttacking.loadFromFile("Resource/Img/Explosion/type_A.png");
	shipAttacking.setSmooth(true);

	sf::Font font;
	font.loadFromFile("Resource/Font/Lato-Black.ttf");

game:
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(sf::Vector2f(24, 10));
	text.setFillColor(sf::Color(0, 83, 37));
	text.setString(std::to_string(0));

	sf::RectangleShape scoreBoard(sf::Vector2f(text.getCharacterSize() * 5, text.getCharacterSize() * 2));
	scoreBoard.setPosition(sf::Vector2f(0, 0));
	scoreBoard.setOutlineThickness(-4);
	scoreBoard.setFillColor(sf::Color(101, 210, 112));
	scoreBoard.setOutlineColor(sf::Color(232, 142, 34));

	sf::RectangleShape maxKiBar(sf::Vector2f(100, 20));
	maxKiBar.setFillColor(sf::Color::Black);
	maxKiBar.setOutlineThickness(4);
	maxKiBar.setOutlineColor(sf::Color(232, 142, 34));
	maxKiBar.setPosition(sf::Vector2f(text.getCharacterSize() * 5, 24));

	sf::RectangleShape currentKiBar(sf::Vector2f(100, 20));
	currentKiBar.setFillColor(sf::Color(0, 0, 204));
	currentKiBar.setPosition(sf::Vector2f(text.getCharacterSize() * 5, 24));

	sf::RectangleShape maxHpBar(sf::Vector2f(120, 20));
	maxHpBar.setFillColor(sf::Color::Black);
	maxHpBar.setOutlineThickness(4);
	maxHpBar.setOutlineColor(sf::Color(232, 142, 34));
	maxHpBar.setPosition(sf::Vector2f(text.getCharacterSize() * 5, 0));

	sf::RectangleShape currentHpBar(sf::Vector2f(120, 20));
	currentHpBar.setFillColor(sf::Color(204, 0, 0));
	currentHpBar.setPosition(sf::Vector2f(text.getCharacterSize() * 5, 0));

	SpaceShip spaceShip(&window);
	std::vector<Ufo> ufos;
	std::vector<Bullet> bullets;
	std::vector<Animation> explosions;

	unsigned long long score = 0;

	sf::Clock clock;
	double ufoTime = 0;
	int bgPosition = 2048 - ScreenHeight;
	unsigned short currentSkill = 1;
	srand(time(NULL));

	sf::CircleShape circle(circleRadius);
	circle.setOrigin(sf::Vector2f(circleRadius, circleRadius));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(-2);
	circle.setPointCount(300);
	circle.setPosition(spaceShip.getPosition());

	sf::Texture skillImage;
	skillImage.loadFromFile("Resource/Img/logo1.png");
	sf::RectangleShape skill1Image(sf::Vector2f(33, 33));
	skill1Image.setTexture(&skillImage);
	skill1Image.setOutlineThickness(3);
	skill1Image.setOutlineColor(sf::Color(81, 255, 0));
	skill1Image.setOrigin(sf::Vector2f(0, 33));
	skill1Image.setPosition(sf::Vector2f(33, ScreenHeight - 33));
	sf::Texture skillImage2;
	skillImage2.loadFromFile("Resource/Img/logo2.png");
	sf::RectangleShape skill2Image(sf::Vector2f(33, 33));
	skill2Image.setTexture(&skillImage2);
	skill2Image.setOutlineThickness(3);
	skill2Image.setOutlineColor(sf::Color(232, 142, 34));
	skill2Image.setOrigin(sf::Vector2f(0, 33));
	skill2Image.setPosition(sf::Vector2f(99, ScreenHeight - 33));

	sf::RectangleShape skill2Bar(sf::Vector2f(33, 33));
	skill2Bar.setFillColor(sf::Color(0, 0, 0, 160));
	skill2Bar.setOrigin(sf::Vector2f(0, 0));
	skill2Bar.setPosition(sf::Vector2f(99, ScreenHeight - 33));

	sf::RectangleShape skill1Bar(sf::Vector2f(33, 33));
	skill1Bar.setFillColor(sf::Color(0, 0, 0, 160));
	skill1Bar.setOrigin(sf::Vector2f(0, 0));
	skill1Bar.setPosition(sf::Vector2f(33, ScreenHeight - 33));
	bool ended = false;
	while (window.isOpen()) {
		ufoTime += clock.getElapsedTime().asSeconds();
		spaceShip.skillsUpdate(clock.getElapsedTime().asSeconds());
		spaceShip.addKi(clock.getElapsedTime().asSeconds());
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}
		if (!ended) {
			bgSprite.setTextureRect(sf::IntRect(0, bgPosition, 1024, ScreenHeight));
			if (bgPosition > ScreenHeight - 1)
				bgPosition -= 1;
			else bgPosition = 2048 - ScreenHeight;
			spaceShip.update();
			if (spaceShip.isDead()) ended = true;
			circle.setPosition(spaceShip.getPosition());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {

				currentSkill = 1;
				skill2Image.setOutlineColor(sf::Color(232, 142, 34));
				skill1Image.setOutlineColor(sf::Color(81, 255, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
				currentSkill = 2;
				skill1Image.setOutlineColor(sf::Color(232, 142, 34));
				skill2Image.setOutlineColor(sf::Color(81, 255, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (spaceShip.skillAvailable(currentSkill))) {
				switch (currentSkill)
				{
				case 1:
				{
					spaceShip.useSkill(currentSkill);
					Bullet newBullet = Bullet(&window, spaceShip, bulletTexture);
					bullets.push_back(newBullet);
					break;
				}
				case 2:
				{
					spaceShip.useSkill(currentSkill);
					explosions.push_back(Animation(&window, skill2, spaceShip.getPosition(), 256, 256, 0.8, 2));
					for (unsigned int j = 0; j < ufos.size(); ) {
						double dx = ufos.at(j).getPosition().x - spaceShip.getPosition().x;
						double dy = ufos.at(j).getPosition().y - spaceShip.getPosition().y;
						double distance = std::sqrt(dx * dx + dy * dy);
						if (distance < circleRadius + ufoRadius) {
							spaceShip.upHp();
							score += (ScreenHeight - static_cast<int>(ufos.at(j).getPosition().y)) / 10;
							explosions.push_back(Animation(&window, ufoExplosion, ufos.at(j).getPosition(), 192, 192, 0.8, 1));
							ufos.erase(ufos.begin() + j);
						}
						else j++;
					}
					break;
				}

				default:
					break;
				}
			}


			if (ufoTime > 1.0) {
				ufos.push_back(Ufo(&window, ufoTexture, clock));
				ufoTime = 0;
			}

			for (unsigned int i = 0; i < bullets.size(); i++) {
				bullets.at(i).update();
				if (bullets.at(i).isOver()) {
					bullets.erase(bullets.begin() + i);
					continue;
				}

				for (unsigned int j = 0; j < ufos.size(); j++) {
					if (ufos.at(j).isKilled(bullets.at(i))) {
						score += (ScreenHeight - static_cast<int>(ufos.at(j).getPosition().y)) / 10;
						explosions.push_back(Animation(&window, ufoExplosion, bullets.at(i).getPosition(), 192, 192, 0.8, 1));
						ufos.erase(ufos.begin() + j);
						bullets.erase(bullets.begin() + i);
						spaceShip.upHp();
						break;
					}
				}

			}

			for (unsigned int i = 0; i < ufos.size();) {
				if (ufos.at(i).isOutScreen() || ufos.at(i).isAttacking(spaceShip)) {
					spaceShip.downHp();
					if (ufos.at(i).isAttacking(spaceShip)) explosions.push_back(Animation(&window, ufoExplosion, ufos.at(i).getPosition(), 192, 192, 0.8, 2));
					ufos.erase(ufos.begin() + i);
				}
				else {
					ufos.at(i).update();
					i++;
				}
			}
			for (unsigned int i = 0; i < explosions.size(); i++)
				if (explosions.at(i).isEnded()) {
					explosions.erase(explosions.begin() + i);
				}
			for (unsigned int i = 0; i < explosions.size(); i++) {
				explosions.at(i).update();
			}


			text.setString(std::to_string(score));
			text.setPosition(sf::Vector2f(55 - text.getGlobalBounds().width / 2, 10));
			currentKiBar.setSize(sf::Vector2f(maxKiBar.getSize().x * spaceShip.getPercentKi(), 20));
			currentHpBar.setSize(sf::Vector2f(maxHpBar.getSize().x * spaceShip.getPercentHp(), 20));
			skill1Bar.setSize(sf::Vector2f(33, -(1 - spaceShip.getSkill(1).getTimer() / spaceShip.getSkill(1).getRecoveryTime()) * skill1Image.getSize().y));
			skill2Bar.setSize(sf::Vector2f(33, -(1 - spaceShip.getSkill(2).getTimer() / spaceShip.getSkill(2).getRecoveryTime()) * skill2Image.getSize().y));

		}
		window.clear(sf::Color::Black);
		window.draw(bgSprite);
		for (unsigned int i = 0; i < bullets.size(); i++) bullets.at(i).draw();
		spaceShip.draw();
		for (unsigned int i = 0; i < ufos.size(); i++) ufos.at(i).draw();
		for (unsigned int i = 0; i < explosions.size(); i++) explosions.at(i).draw();
		if (currentSkill == 2) window.draw(circle);
		window.draw(maxHpBar);
		window.draw(currentHpBar);
		window.draw(maxKiBar);
		window.draw(currentKiBar);
		window.draw(scoreBoard);
		window.draw(text);
		window.draw(skill1Image);
		window.draw(skill2Image);
		window.draw(skill1Bar);
		window.draw(skill2Bar);
		if (ended) {
			sf::RectangleShape pauseRect(sf::Vector2f(ScreenWidth, ScreenHeight));
			pauseRect.setFillColor(sf::Color(0, 0, 0, 170));
			window.draw(pauseRect);
			sf::RectangleShape pauseBoard(sf::Vector2f(ScreenWidth * 0.8, ScreenHeight / 2));
			pauseBoard.setOrigin(sf::Vector2f(ScreenWidth * 0.4, ScreenHeight / 4));
			pauseBoard.setPosition(sf::Vector2f(ScreenWidth / 2, ScreenHeight / 2));
			pauseBoard.setFillColor(sf::Color(101, 210, 112, 200));
			window.draw(pauseBoard);
			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setString("Game Over!");
			gameOverText.setCharacterSize(40);
			gameOverText.setFillColor(sf::Color(160, 0, 0));
			gameOverText.setPosition(sf::Vector2f(ScreenWidth / 2 - gameOverText.getLocalBounds().width / 2, ScreenHeight / 3));
			window.draw(gameOverText);
			sf::Text scoreText;
			scoreText.setFont(font);
			scoreText.setCharacterSize(30);
			scoreText.setString("Score : " + std::to_string(score));
			scoreText.setFillColor(sf::Color(0, 103, 0));
			scoreText.setPosition(sf::Vector2f(ScreenWidth / 2 - scoreText.getLocalBounds().width / 2, ScreenHeight / 2 - 15));
			window.draw(scoreText);
			sf::Texture replay;
			replay.loadFromFile("Resource/Img/replayBtn.png");
			replay.setSmooth(true);
			sf::Sprite replayBtn;
			replayBtn.setTexture(replay);
			replayBtn.setOrigin(sf::Vector2f(replay.getSize().x / 2, replay.getSize().y / 2));
			replayBtn.setPosition(sf::Vector2f(ScreenWidth / 3 * 2 + 10, ScreenHeight / 2 + ScreenWidth / 6 + 20));

			sf::Texture quit;
			quit.loadFromFile("Resource/Img/quitBtn.png");
			quit.setSmooth(true);
			sf::Sprite quitBtn;
			quitBtn.setTexture(quit);
			quitBtn.setOrigin(sf::Vector2f(quit.getSize().x / 2, quit.getSize().y / 2));
			quitBtn.setPosition(sf::Vector2f(ScreenWidth / 3 - 10, ScreenHeight / 2 + ScreenWidth / 6 + 20));

			if (sf::Mouse::getPosition(window).x >= quitBtn.getPosition().x - quit.getSize().x / 2 &&
				sf::Mouse::getPosition(window).x <= quitBtn.getPosition().x + quit.getSize().x / 2 &&
				sf::Mouse::getPosition(window).y >= quitBtn.getPosition().y - quit.getSize().y / 2 &&
				sf::Mouse::getPosition(window).y <= quitBtn.getPosition().y + quit.getSize().y / 2) {
				quitBtn.setColor(sf::Color::Color(210, 80, 0));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					window.close();
				}
			}

			if (sf::Mouse::getPosition(window).x >= quitBtn.getPosition().x - quit.getSize().x / 2 &&
				sf::Mouse::getPosition(window).x <= quitBtn.getPosition().x + quit.getSize().x / 2 &&
				sf::Mouse::getPosition(window).y >= quitBtn.getPosition().y - quit.getSize().y / 2 &&
				sf::Mouse::getPosition(window).y <= quitBtn.getPosition().y + quit.getSize().y / 2) {
				quitBtn.setColor(sf::Color::Color(210, 80, 0));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					window.close();
				}
			}
			if (sf::Mouse::getPosition(window).x >= replayBtn.getPosition().x - replay.getSize().x / 2 &&
				sf::Mouse::getPosition(window).x <= replayBtn.getPosition().x + replay.getSize().x / 2 &&
				sf::Mouse::getPosition(window).y >= replayBtn.getPosition().y - replay.getSize().y / 2 &&
				sf::Mouse::getPosition(window).y <= replayBtn.getPosition().y + replay.getSize().y / 2) {
				replayBtn.setColor(sf::Color::Color(210, 80, 0));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					goto game;
				}
			}
			window.draw(quitBtn);
			window.draw(replayBtn);

		}

		window.display();
	}
	return;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Space Shooting", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Image icon;
	icon.loadFromFile("Resource/Img/game_logo.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	MainGame(window);
	return 0;
}
