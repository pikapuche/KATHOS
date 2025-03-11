#include "Gemme.hpp"

Gemme::Gemme(float s, float jForce) : Player() {
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
		isTakeDash = true;
		clock.restart();
	}

	if (Keyboard::isKeyPressed(Keyboard::A) && isTakeDash && !isDashing && coolDownDash.getElapsedTime().asMilliseconds() >= 1500 ) {
		isDashing = true;
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

void Gemme::draw(RenderWindow& window)
{
	if (isTakeSpeed == false) {
		window.draw(speedGemmeShape);
	}
	if (isTakeDash == false) {
		window.draw(dashGemmeShape);
	}
}
