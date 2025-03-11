#include "Player.hpp"

Player::Player(float s, float jForce) : Entity(position.x, position.y) { // constructeur de base 
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(40.0f, 40.0f));
    velocity.y = 0;  // Pas de mouvement vertical au départ
    isJumping = false;
    isJumping2 = false;
    isAttacking = false;
    attackShape.setSize(sf::Vector2f(10.0f, 20.0f));
    attackShape.setFillColor(sf::Color::Red);
}

void Player::movementManager(float deltaTime) { 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { position.x -= SPEED * deltaTime; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { position.x += 1 + SPEED * deltaTime; }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { jump(); }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { isAttacking = true; }

    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;

    shape.setPosition(position);
    attackShape.setPosition(position.x + 40, position.y + 20);
}

void Player::jump() {

    if (isGrounded) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        isGrounded = false;
        isJumping = true;
        velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut pour sauter 
        jumpCount = 1;
        jumpClock.restart();
    }
    else if (jumpCount < 2 && jumpClock.getElapsedTime().asMilliseconds() >= 175) {
        velocity.y = -jumpForce;
        jumpCount = 2;
    }
}

void Player::attack(float deltaTime) {
    if (isAttacking) {
        animTimeDecr += deltaTime;
        if (animTimeDecr > 0.008) {
            rotaLeft += 10;
            attackShape.setRotation(rotaLeft); // 220
            if (rotaLeft >= 300) {
                rotaLeft = 220;
                isAttacking = false;
                cout << "ouiiiiiiiiiiiiiiiiiii" << endl << endl;
            }
            animTimeDecr = 0;
        }
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

bool Player::getIsJumping2() {
    return isJumping2;
}

bool Player::setIsJumping2(bool jump) {
    isJumping2 = jump;
    return isJumping2;
}

bool Player::getCanJump()
{
    return canJump;
}

bool Player::setcanJump(bool can)
{
    canJump = can;
    return canJump;
}

bool Player::getCanJump2()
{
    return canJump2;
}

bool Player::setcanJump2(bool can)
{
    canJump2 = can;
    return canJump2;
}

bool Player::setIsGrounded(bool is)
{
    isGrounded = is;
    return isGrounded;
}

bool Player::getIsGrounded()
{
    return isGrounded;
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

float Player::setSPEED(float speed) {
    SPEED = speed;
    return SPEED;
}


int Player::setJumpCount(float count)
{
    jumpCount = count;
    return jumpCount;
}

int Player::getJumpCount()
{
    return jumpCount;
}

void Player::update(float deltaTime) {
    movementManager(deltaTime);
    attack(deltaTime);
}

void Player::draw(RenderWindow& window) {
    window.draw(shape);
    if (isAttacking) window.draw(attackShape);
}