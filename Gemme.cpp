#include "Gemme.hpp"

Gemme::Gemme() : Player() {
	/*speedGemmeShape.setSize(Vector2f(32, 32));
	dashGemmeShape.setSize(Vector2f(32, 32));*/
	gemmeTexture.loadFromFile("Assets/Map/gemme.png");
	gemmeSprite.setTexture(gemmeTexture);
	gemmeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

sf::Vector2f Gemme::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	return position;
}

void movementManager(float deltaTime) {


};

void Gemme::update(float deltaTime) {
	movementManager(deltaTime);
	//attack(deltaTime);
	//dash(deltaTime);
	//animationManager(deltaTime);
}
void Gemme::interact(Player& player)
{
	if (speedGemmeShape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
		player.setIsTakeSpeed(true);
		cout << "est r�cup";
	}

	if (dashGemmeShape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
		player.setIsTakeDash(true);
		clock.restart();
	}

	dashGemmeShape.setPosition(position);
	speedGemmeShape.setPosition(position);
}

void Gemme::draw(RenderWindow& window, Player& player)
{
	if (!player.getIsTakeSpeed()) {
		window.draw(speedGemmeShape);
	}
	if (!player.getIsTakeDash()) {
		window.draw(dashGemmeShape);
	}
}
