#include "Player.hpp"

Player::Player(float s, float jForce) : Entity(position.x, position.y) { // constructeur de base 
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(40.0f, 40.0f));
    velocity.y = 0;  // Pas de mouvement vertical au départ
    isJumping = false;
    isAttacking = false;
    attackShape.setSize(sf::Vector2f(10.0f, 10.0f));
    attackShape.setFillColor(sf::Color::Red);
    attackShape.setOrigin(position.x + 30, position.y + 10);
}

void Player::movementManager(float deltaTime) { 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { position.x -= SPEED * deltaTime; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { position.x += 1 + SPEED * deltaTime; }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { jump(); }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { attack(deltaTime); }
    
    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;

    shape.setPosition(position);
    attackShape.setPosition(position);
}

void Player::jump() {
    if (!isJumping) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        isJumping = true;
        velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut pour sauter 
    }
}

void Player::attack(float deltaTime) {
    isAttacking = true;
    animTimeDecr += deltaTime;
    if (animTimeDecr > 0.008) {
        rotaLeft -= 10;
        attackShape.setRotation(rotaLeft); // 220
        if (rotaLeft <= -150) {
            rotaLeft = -46;
            isAttacking = false;
            cout << "ouiiiiiiiiiiiiiiiiiii" << endl << endl;
        }
        animTimeDecr = 0;
    }
}

Vector2f Player::getPosPos() {
    return position;
}

Vector2f Player::setPosPos(float(x), float(y)) {
    position.x = x;
    position.y = y;
    return position;
}

Vector2f Player::getVelocity() {
    return velocity;
}

Vector2f Player::setVelocity(float veloX, float veloY) {
    velocity.x = veloX;
    velocity.y = veloY;
    return velocity;
}

RectangleShape Player::getShape() {
    return shape;
}

bool Player::getIsJumping() {
    return isJumping;
}

bool Player::setIsJumping(bool jump) {
    isJumping = jump;
    return isJumping;
}

float Player::getJumpForce() {
    return jumpForce;
}

float Player::setJumpForce(float force) {
    jumpForce = force;
    return jumpForce;
}

float Player::getGravity() {
    return gravity;
}

float Player::getSPEED() {
    return SPEED;
}

void Player::update(float deltaTime) {
    movementManager(deltaTime);
}

void Player::draw(RenderWindow& window) {
    window.draw(shape);
    if (isAttacking) window.draw(attackShape);
}