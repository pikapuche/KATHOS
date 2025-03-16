#include "Boss.hpp"

Boss::Boss(Player& target) : Entity(position.x, position.y), target(target) {
    texture.loadFromFile("Assets/Boss/boss.png");
    sprite.setTexture(texture);
    sprite.setScale(Vector2f(0.22f, 0.22f));
    speed = 200.0f;
    velocity = { -speed, 0.0f };
    detectionRange = 600.0f;
    boxCol1 = 35;
    boxCol2 = 58;
    state = GROUNDED;
}

void Boss::jump()
{
    if (state == GROUNDED) {
        state = JUMP;
        velocity.y = -jumpForce;
        jumpClock.restart();
    }
}

void Boss::getDown()
{
    if (state == JUMP) {
        state = GROUNDED;
        velocity.y = jumpForce;
        jumpClock.restart();
    }
}

bool Boss::canSeePlayer() {
    float distanceX = abs(target.getPosPos().x - position.x);
    float distanceY = abs(target.getPosPos().y - position.y);
    return (distanceX < detectionRange && distanceY < 50.0f);
}

void Boss::chasePlayer() {
    if (target.getPosPos().x > position.x) {
        velocity.x = speed;
    }
    else {
        velocity.x = -speed;
    }
}

void Boss::update(float deltaTime) {
    if (canSeePlayer()) {
        chasePlayer();
    }

    position += velocity * deltaTime;
    checkCollision(1920, 1080);
    sprite.setPosition(position);

    onestla = rand() % 5;

    switch (onestla) {
    case 0:
        break;
    case 1:
        if (state == JUMP) getDown();
        break;
    case 2:
        if (state == GROUNDED) jump();
        break;
    case 3:
        if (state == JUMP) getDown();
        break;
    case 4:
        if (state == GROUNDED) jump();
        break;
    }
}

void Boss::draw(RenderWindow& window) {
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

Vector2f Boss::getVelocity() {
    return velocity;
}

Vector2f Boss::setVelocity(float veloX, float veloY) {
    velocity.x = veloX;
    velocity.y = veloY;
    return velocity;
}

float Boss::getJumpForce() {
    return jumpForce;
}

float Boss::setJumpForce(float force) {
    jumpForce = force;
    return jumpForce;
}

float Boss::getGravity() {
    return gravity;
}