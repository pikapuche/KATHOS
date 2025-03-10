#include "Player.hpp"

Player::Player(float s, float jForce) : Entity(position.x, position.y) { // constructeur de base 
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(40.0f, 40.0f));
    velocity.y = 0;  // Pas de mouvement vertical au départ
    isJumping = false;
}

void Player::movementManager(float deltaTime) { 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { position.x -= SPEED * deltaTime; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { position.x += 1 + SPEED * deltaTime; }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { jump(); }

    
    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;

    shape.setPosition(position);
}

void Player::jump() {
    if (!isJumping) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        isJumping = true;
        velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut pour sauter 
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
}