#include "Boss.hpp"

Boss::Boss(Player& target) : Entity(position.x, position.y), target(target) { //constructeur du boss
    texture.loadFromFile("Assets/Boss/boss.png");
    sprite.setTexture(texture);
    sprite.setScale(Vector2f(0.22f, 0.22f));
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
    speed = 200.0f;
    velocity = { -speed, 0.0f };
    detectionRange = 600.0f;
}

bool Boss::canSeePlayer()
{
    float distanceX = std::abs(target.getPosPos().x - position.x);
    float distanceY = std::abs(target.getPosPos().y - position.y);

    return (distanceX < detectionRange && distanceY < 50.0f);
}

void Boss::chasePlayer()
{
    if (target.getPosPos().x > position.x)
    {
        velocity.x = speed;
    }
    else {
        velocity.x = -speed;
    }
}

void Boss::update(float deltaTime) { //déplacements
    if (canSeePlayer()) {
        chasePlayer();
    }
    position += velocity * deltaTime;
    sprite.setPosition(position);
}

void Boss::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Boss::checkCollision(int mapWidth) { //check les collisions et empêche le boss de partir hors de la map sinon c'est pas ouf
    if (position.x <= 0) {
        position.x = 0;
        velocity.x = speed;
    }
    else if (position.x + sprite.getScale().x >= mapWidth) {
        position.x = mapWidth - sprite.getScale().x;
        velocity.x = -speed;
    }
}

Vector2f Boss::getPos() {
    return position;
}

Vector2f Boss::setPos(float(x), float(y)) {
    position.x = x;
    position.y = y;
    return position;
}