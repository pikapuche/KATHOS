#include "Player.hpp"

Player::Player() : Entity(texture, position.x, position.y) { // constructeur de base 
    //shape.setSize(sf::Vector2f(40.0f, 40.0f));
    velocity.y = 0; // Pas de mouvement vertical au depart
    attackShape.setSize(sf::Vector2f(10.0f, 20.0f));
    attackShape.setFillColor(sf::Color::Red);
    textureSprint.loadFromFile("assets/texture/player/piskelVersion.png");
    sprite.setTexture(textureSprint);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Player::movementManager(float deltaTime) { 

    if (!isDashing) {
        if (joystickValue > 10 && joystickValue < -10) {
            position.x += 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickValue < -10) { position.x -= SPEED * deltaTime; stateLook = LOOK_LEFT; stateMove = RUN; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickValue > 10) { position.x += 1 + SPEED * deltaTime; stateLook = LOOK_RIGHT; stateMove = RUN; }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)) { jump(); }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 2)) { isAttacking = true; }

    // Si la gâchette gauche est pressée ou que A est pressée OU si la gâchette droite est pressée ou que A est pressée
    if (((Keyboard::isKeyPressed(Keyboard::A) || gachetteValue > 10) || (Keyboard::isKeyPressed(Keyboard::A) || gachetteValue < -10)) && isTakeDash && !isDashing && coolDownDash.getElapsedTime().asMilliseconds() >= 1500) {
        isDashing = true;
        clock.restart();
    }

    if ((Keyboard::isKeyPressed(Keyboard::LShift) || sf::Joystick::isButtonPressed(0, 8)) && isTakeSpeed) {
        SPEED = 600;
    }
    else {
        SPEED = 300;
    }

    //////////////////////////////  Manette  //////////////////////////////////

    if (sf::Joystick::isConnected(0))
    {
        // Verification des gechettes (left = 10 & right = -10)
        gachetteValue = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

        joystickValue = sf::Joystick::getAxisPosition(0, sf::Joystick::X); // donne la poussée du joystick gauche sur l'axe X

    }

    if (isGrounded) {
        velocity.y = 0;
    }
    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;
    
    //shape.setPosition(position);
    sprite.setPosition(position);
}

void Player::animationManager(float deltaTime) {
    switch (stateMove)
    {
    case RUN:
        animRunTimeDecr += deltaTime;
        anim_move.y = 0;
        if (animRunTimeDecr > 0.08f) {
            anim_move.x++;
            animRunTimeDecr = 0;
        }
        if (stateLook == LOOK_LEFT) {
            if (anim_move.x > 6) 
                anim_move.x = 1;
            sprite.setTextureRect(sf::IntRect(anim_move.x * 32, anim_move.y * 32, -32, 32));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_move.x > 5)
                anim_move.x = 0;
            sprite.setTextureRect(sf::IntRect(anim_move.x * 32, anim_move.y * 32, 32, 32));
        }
        break;
    }
}

void Player::jump() {

    if (isGrounded) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        isGrounded = false;
        isJumping = true;
        velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut pour sauter 
        jumpCount = 1;
        jumpClock.restart();
    }
    else if (jumpCount == 1 && jumpClock.getElapsedTime().asMilliseconds() >= 175 && !isGrounded) { // compteur permettant de savoir si on peut faire un deuxième saut
        velocity.y = -jumpForce;
        jumpCount = 2;
    }
}

void Player::attack(float deltaTime) {
    // Si le perso a une épée on fait une rotation a l'arme
    if (isAttacking) {
        if (stateLook == LOOK_RIGHT) {
            attackShape.setPosition(position.x + 40, position.y + 20);
            animTimeDecr += deltaTime;
            if (animTimeDecr > 0.008) {
                rotaRight += 10;
                attackShape.setRotation(rotaRight);
                if (rotaRight >= 300) {
                    rotaRight = 220;
                    isAttacking = false;
                }
                animTimeDecr = 0;
            }
        }
        if (stateLook == LOOK_LEFT) {
            attackShape.setPosition(position.x - 20, position.y + 20);
            animTimeDecr += deltaTime;
            if (animTimeDecr > 0.008) {
                rotaRight -= 10;
                attackShape.setRotation(rotaRight);
                if (rotaRight <= -100) {
                    rotaRight = -20;
                    isAttacking = false;
                }
                animTimeDecr = 0;
            }
        }
    }
}

void Player::dash(float deltaTime)
{
    if (isDashing) {
        if (stateLook == LOOK_LEFT) {
            SPEED = 2000;
            position.x -= 2 + SPEED * deltaTime;
        }
        if (stateLook == LOOK_RIGHT) {
            SPEED = 2000;
            position.x += 2 + SPEED * deltaTime;
        }
        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            isDashing = false;
            SPEED = 300.f;
            coolDownDash.restart();
            cout << "dash stop" << endl;
        }
    }
}

Vector2f Player::setPosPos(float x, float y)
{
    position.x = x;
    position.y = y;
    return position;
}

Vector2f Player::getPosPos()
{
    return position;
}

#pragma region Getteurs / Setteurs

Vector2f Player::getVelocity() {
    return velocity;
}

Vector2f Player::setVelocity(float veloX, float veloY) {
    velocity.x = veloX;
    velocity.y = veloY;
    return velocity;
}

//RectangleShape Player::getShape() {
//    return shape;
//}

bool Player::getIsJumping() {
    return isJumping;
}

bool Player::setIsJumping(bool jump) {
    isJumping = jump;
    return isJumping;
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

bool Player::getIsTakeDash()
{
    return isTakeDash;
}

bool Player::setIsTakeDash(bool dash)
{
    isTakeDash = dash;
    return isTakeDash;
}

bool Player::getIsDashing()
{
    return isDashing;
}

bool Player::setIsDashing(bool dash)
{
    isDashing = dash; 
    return isDashing;
}

bool Player::getIsTakeSpeed()
{
    return isTakeSpeed;
}

bool Player::setIsTakeSpeed(bool speed)
{
    isTakeSpeed = speed;
    return isTakeSpeed;
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

bool Player::getHasKey() {
    return hasKey;
}
bool Player::setHasKey(bool key) {
    hasKey = key;
    return hasKey;
}

#pragma endregion Getteurs / Setteurs

void Player::update(float deltaTime) {
    movementManager(deltaTime);
    attack(deltaTime);
    dash(deltaTime);
    animationManager(deltaTime);
}

void Player::draw(RenderWindow& window) {
    window.draw(sprite);
    if (isAttacking) window.draw(attackShape);
}