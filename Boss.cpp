#include "Boss.hpp"

Boss::Boss() : Entity(position.x, position.y) {
    texture.loadFromFile("Assets/texture/Boss/boss.png");
    sprite.setTexture(texture);
    sprite.setScale(Vector2f(1.5f, 1.5f));
    speed = 200.0f;
    velocity.y = 0;
    detectionRange = 400.0f;
    detectionRect.setSize(Vector2f(detectionRange, 64));
    detectionRect.setFillColor(Color(0, 255, 0, 50));
    detectionRect.setOrigin(368, 0);
    boxCol1 = 64;
    boxCol2 = 64;
    state = GROUNDED;
}

void Boss::jump()
{
    if (state == GROUNDED) {
        state = JUMP;
        isJumping = true;
        velocity.y = -jumpForce;
        jumpClock.restart();
    }
}

void Boss::takeDamage(Player& player)
{
    if (player.ATTACKING) {
        if (player.getAttackShape().getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            setLife(-10);
            cout << "aie ca fais mal (boss)" << endl;
        }
    }
}

//bool Boss::canSeePlayer() {
//    float distanceX = abs(target.getPosPos().x - position.x);
//    float distanceY = abs(target.getPosPos().y - position.y);
//    return (distanceX < detectionRange && distanceY < 50.0f);
//}

void Boss::movementManager(float pos, float pos2, float deltaTime) { // permet de gerer le mouvement de l'ennemi
    //if (canSeePlayer())
    //{

    //}
    if (!isJumping) {
        if (position.x < pos && directionState != RIGHT) { // faire en sorte qu'il ne puisse pas changer de direction pendant un saut
            directionState = RIGHT;
        }
        else if (position.x > pos2 && directionState != LEFT) {
            directionState = LEFT;
        }
    }

    if (directionState == RIGHT) {
        position.x += speed * deltaTime;
    }
    else {
        position.x -= speed * deltaTime;
    }

    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;

    sprite.setPosition(position);
    detectionRect.setPosition(position);

    if (sprite.getPosition().y < 0) { // haut de l'écran
        sprite.setPosition(position.x, position.y = 64);
    }
    //if (sprite.getPosition().y > 1016) { // bas de l'écran 
    //    sprite.setPosition(position.x, position.y = 1016);
    //}
    if (sprite.getPosition().x < 0) { // gauche de l'écran
        sprite.setPosition(position.x = 0, position.y);
    }
    if (sprite.getPosition().x > 1856) { // droite de l'écran
        sprite.setPosition(position.x = 1856, position.y);
    }
}

void Boss::update(float deltaTime, Player& player) {

    if (jumpClock.getElapsedTime().asSeconds() <= 2) {
        onestla = rand() % 5;
    }

    switch (onestla) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        jump();
        break;
    case 3:
        break;
    case 4:
        jump();
        break;
    }

    if (state == GROUNDED) {
        isJumping = false;
    }

    movementManager(player.getSprite().getPosition().x, player.getSprite().getPosition().x, deltaTime);
}

void Boss::draw(RenderWindow& window) {
    window.draw(sprite);
    window.draw(detectionRect);
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