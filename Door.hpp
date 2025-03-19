#pragma once
#include "Interactibles.hpp"

class Door : public Interactible {
private:
	sf::Vector2f DEFAULT_SCALE = { 1.0f,1.0f };
	sf::Vector2f guiPos = { 20.0f, 70.0f };

	bool isOpen = false;
	sf::Texture doorOpenTexture;
	bool typeButton;
public:
	Door(bool typeButton);
	bool isDoor() const override { return true; }  // Doors return true
	void interact(const std::shared_ptr<Player>& player) override;
	void updateProximity(const std::shared_ptr<Player>& player, sf::RenderWindow& window) override;
	void setPosPos(float x, float y);
	void draw(RenderWindow& window) override;
	void openDoor(bool open);
	void collision(const std::shared_ptr<Player>& player);
	void rotateCheck(const std::shared_ptr<Player>& player);
};