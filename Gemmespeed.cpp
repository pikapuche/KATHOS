#include "GemmeSpeed.hpp"

GemmeSpeed::GemmeSpeed() : Gemme() {
	shape.setSize(Vector2f(32, 32));
}

void GemmeSpeed::interact(Player& player)
{
	if (shape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
		player.setIsTakeSpeed(true);
		cout << "est récup";
	}
	shape.setPosition(position);
}

void GemmeSpeed::draw(RenderWindow& window, Player& player)
{
	if (!player.getIsTakeSpeed()) {
		window.draw(shape);
	}
}
