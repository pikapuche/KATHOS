#include "Boss.hpp"

Boss::Boss(Player& target) : target(target) { //constructeur du boss
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    speed = 200.0f;
    velocity = { -speed, 0.0f };
    detectionRange = 300.0f;
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
    shape.setPosition(position);
}

void Boss::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Boss::checkCollision(int mapWidth) { //check les collisions et empêche le boss de partir hors de la map sinon c'est pas ouf
    if (position.x <= 0) {
        position.x = 0;
        velocity.x = speed; 
    }
    else if (position.x + shape.getSize().x >= mapWidth) {
        position.x = mapWidth - shape.getSize().x;
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

sf::RectangleShape Boss::getShape() { //prend la shape du joueur
    return shape;
}