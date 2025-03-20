#include "NuageTox.hpp"

NuageTox::NuageTox() : Entity(position.x, position.y) { //constructeur du nuage
    texture.loadFromFile("Assets/texture/Map/nuage.png");
    sprite.setTexture(texture);
    //sprite.setScale(Vector2f(3.f, 3.f));
    sprite.setColor(Color(255, 255, 255, 200));
}

void NuageTox::draw(RenderWindow& window) {
    window.draw(sprite);
}

void NuageTox::collision(Player& player) {
    if (player.getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds())) {
        if (!slow) {
            coolDownSlow.restart();
        }
        slow = true;
    }

    if (slow && coolDownSlow.getElapsedTime().asSeconds() < 2) { // slow pendant 2 secondes
        player.setSPEED(205.f);
    }
    else if (coolDownSlow.getElapsedTime().asSeconds() >= 2 && slow) {
        slow = false;
    }
}

void NuageTox::update(float deltaTime) { //d�placements
    sprite.setPosition(position);
}

Vector2f NuageTox::getPos() {
    return position;
}

Vector2f NuageTox::setPos(float x, float y) {
    position.x = x;
    position.y = y;
    return position;
}