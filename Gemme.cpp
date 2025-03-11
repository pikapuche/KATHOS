#include "Gemme.hpp"

Gemme::Gemme(float s, float jForce) : Player(s, jForce) {
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
	if (speedGemmeShape.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
		isTakeSpeed = true;
		cout << "est récup";
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift) && isTakeSpeed) {
		player.setSPEED(500);
	}
	else {
		player.setSPEED(300);
	}

	if (dashGemmeShape.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
		player.setIsTakeDash(true);
		clock.restart();
	}

	if (Keyboard::isKeyPressed(Keyboard::A) && player.getIsTakeDash() && !player.getIsDashing() && coolDownDash.getElapsedTime().asMilliseconds() >= 1500) {
		player.setIsDashing(true);
		clock.restart();
	}

	if (player.getIsDashing()) {
		player.setSPEED(2000);
		if (clock.getElapsedTime().asMilliseconds() >= 100) {
			player.setIsDashing(false);
			player.setSPEED(300.f);
			coolDownDash.restart();
		}
	}

	dashGemmeShape.setPosition(position);
	speedGemmeShape.setPosition(position);
}

void Gemme::draw(RenderWindow& window, Player& player)
{
	if (isTakeSpeed == false) {
		window.draw(speedGemmeShape);
	}
	if (!player.getIsTakeDash()) {
		window.draw(dashGemmeShape);
	}
}
