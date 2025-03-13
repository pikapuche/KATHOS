#include "Boss.hpp"
#include <cstdlib> 

Boss::Boss(Player& target) : Entity(position.x, position.y), target(target) {
    texture.loadFromFile("Assets/Boss/boss.png");
    sprite.setTexture(texture);
    sprite.setScale(Vector2f(0.22f, 0.22f));
    speed = 200.0f;
    velocity = { -speed, 0.0f };
    detectionRange = 600.0f;

    isJumping = false;
    jumpTimer = 0;
    jumpHeight = 200.0f;
    gravity = 500.0f;
    timeInAir = 0;
}

bool Boss::canSeePlayer() {
    float distanceX = std::abs(target.getPosPos().x - position.x);
    float distanceY = std::abs(target.getPosPos().y - position.y);
    return (distanceX < detectionRange && distanceY < 50.0f);
}

void Boss::chasePlayer() {
    if (!isJumping) {
        if (target.getPosPos().x > position.x) {
            velocity.x = speed;
        }
        else {
            velocity.x = -speed;
        }
    }
}

void Boss::jumpToPlatform() {
    if (!isJumping) {
        isJumping = true;
        timeInAir = 0;
        velocity.y = -sqrt(2 * gravity * jumpHeight);
    }
}

void Boss::fallBackDown() {
    velocity.y += gravity * 0.016f;
}

void Boss::update(float deltaTime) {
    if (!isJumping) {
        if (rand() % 300 == 0) {
            jumpToPlatform();
        }
    }
    else {
        fallBackDown();
        timeInAir += deltaTime;
        if (timeInAir > 1.0f) {
            isJumping = false;
            velocity.y = 0;
        }
    }

    if (canSeePlayer()) {
        chasePlayer();
    }

    position += velocity * deltaTime;
    checkCollision(1920, 1080);
    sprite.setPosition(position);
}

void Boss::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Boss::checkCollision(int mapWidth, int mapHeight) {
    if (position.x <= 0) {
        position.x = 0;
        velocity.x = speed;
    }
    else if (position.x + sprite.getGlobalBounds().width >= mapWidth) {
        position.x = mapWidth - sprite.getGlobalBounds().width;
        velocity.x = -speed;
    }

    if (position.y <= 0) {
        position.y = 0;
        velocity.y = 0;
    }
    else if (position.y + sprite.getGlobalBounds().height >= mapHeight) {
        position.y = mapHeight - sprite.getGlobalBounds().height;
        isJumping = false;
        velocity.y = 0;
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