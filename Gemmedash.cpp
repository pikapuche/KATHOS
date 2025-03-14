#include "GemmeDash.hpp"

GemmeDash::GemmeDash() : Gemme() { 
	shape.setSize(Vector2f(32, 32));
	shape.setPosition(position);
	shape.setFillColor(Color::Blue);
}

void GemmeDash::interact(Player& player)
{
	if (shape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
		player.setIsTakeDash(true);
		/*player.clock.restart();*/
	}
	shape.setPosition(position);
}

void GemmeDash::draw(RenderWindow& window, Player& player)
{
	if (!player.getIsTakeDash()) {
		window.draw(shape);
	}
}