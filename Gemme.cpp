#include "Gemme.hpp"

Gemme::Gemme() : Player() {
	speedGemmeShape.setSize(Vector2f(32, 32));
	dashGemmeShape.setSize(Vector2f(32, 32));
	isTakeSpeed = false;
	isTakeDash = false;
	isDashing = false;
}

sf::Vector2f Gemme::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	return position;
}

void Gemme::interact(Player& player)
{
	if (speedGemmeShape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
		player.setIsTakeSpeed(true);
		cout << "est récup";
	}

	if (dashGemmeShape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
		player.setIsTakeDash(true);
		clock.restart();
	}

	if (isDashing) {
		player.setSPEED(2000);
		if (clock.getElapsedTime().asMilliseconds() >= 100) {
			isDashing = false;
			player.setSPEED(300.f);
			coolDownDash.restart();
		}
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
