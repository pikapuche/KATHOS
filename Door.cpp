#include "Door.hpp"

Door::Door(bool typeButton) : typeButton(typeButton) {
	texture.loadFromFile("assets/texture/Interactibles/door.png");
	doorOpenTexture.loadFromFile("assets/texture/Interactibles/door_open.png");

	sprite.setTexture(texture);
};

void Door::draw(RenderWindow& window) {
	window.draw(sprite);
}

void Door::setPosPos(float x, float y) {
	this->sprite.setPosition(x, y);
}

void Door::interact(const std::shared_ptr<Player>& player) {
	if (!typeButton) {
		if (!isOpen) {
			if (player->getHasKey() && this->playerTryInteract()) {
				std::cout << "Door opens!" << std::endl;
				isOpen = true; // Update isOpen state
				sprite.setTexture(doorOpenTexture);
				player->setHasKey(false);
			}
		}
	}
}

void Door::openDoor(bool open) {
	isOpen = open;
}