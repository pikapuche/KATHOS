#include "Boss.hpp"

Boss::Boss(Player& target) : Entity(position.x, position.y), target(target) { //constructeur du boss
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    speed = 200.0f;
    velocity = { -speed, 0.0f };
    detectionRange = 400.0f;
}

bool Boss::canSeePlayer()
{
    float distance = std::sqrt(std::pow(target.getPosPos().x - position.x, 2) + std::pow(target.getPosPos().y - position.y, 2));
    return (distance < detectionRange);
}

void Boss::startJump() {
    isJumping = true;
    jumpTimer.restart();
    groundY = position.y;
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

    if (!isJumping && !isFalling) {
        if (rand() % 300 == 0) {
            startJump();
        }
    }

    if (isJumping) {
        position.y += jumpSpeed;
        jumpSpeed += gravity;

        if (jumpTimer.getElapsedTime() >= jumpDuration) {
            isJumping = false;
            isFalling = true;
        }
    }

    if (isFalling) {
        position.y += gravity * 5;

        if (position.y >= groundY) {
            position.y = groundY;
            isFalling = false;
            jumpSpeed = -8.0f;
        }
    }

    sprite.setPosition(position);
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

Vector2f Boss::setPos(float x, float y) {
    position.x = x;
    position.y = y;
    return position;
}

sf::RectangleShape Boss::getShape() { //prend la shape du joueur
    return shape;
}