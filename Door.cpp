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

void Door::rotateCheck(const std::shared_ptr<Player>& player) {
	if (sprite.getPosition().x > player->getPosPos().x) {
		sprite.setScale(DEFAULT_SCALE);
	}
	else if (sprite.getPosition().x < player->getPosPos().x) {
		sprite.setScale(DEFAULT_SCALE.x * -1, DEFAULT_SCALE.y);
		sprite.setPosition((sprite.getPosition().x + sprite.getGlobalBounds().getSize().x), sprite.getPosition().y);
	}

}

void Door::collision(const std::shared_ptr<Player>& player) {
	Vector2f previousPos = player->getPosPos();

	if (sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()) && (player->getPosPos().x < sprite.getPosition().x)) {
		player->setPosPos(previousPos.x - 5.1, previousPos.y);
	}


	if (sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds()) && (player->getPosPos().x > sprite.getPosition().x)) {
		player->setPosPos(previousPos.x + 5.1, previousPos.y);
	}
}


void Door::interact(const std::shared_ptr<Player>& player) {
	if (!isOpen) {
		collision(player);
		if (!typeButton) {
			if (player->getHasKey() && this->playerTryInteract()) {
				std::cout << "Door opens!" << std::endl;
				isOpen = true; // Update isOpen state
				rotateCheck(player);
				sprite.setTexture(doorOpenTexture);

				player->setHasKey(false);
			}
		}
	}
}

void Door::openDoor(bool open) {
	isOpen = open;
}


