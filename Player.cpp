#include "Player.hpp"

Player::Player() : Entity(texture, position.x, position.y) { // constructeur de base 
    velocity.y = 0; // Pas de mouvement vertical au depart
    attackShape.setSize(sf::Vector2f(10.0f, 20.0f));
    attackShape.setFillColor(sf::Color::Red);
    textureSprint.loadFromFile("assets/texture/player/piskelVersion3.png");
    textureIdle.loadFromFile("assets/texture/player/idleV2.png");
    sprite.setTexture(textureSprint);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Player::movementManager(float deltaTime) { 

    if (stateMove == IDLE) {
        sprite.setTexture(textureIdle);
    }
    else if (stateMove == RUN) {
        sprite.setTexture(textureSprint);
    }

    if (!isDashing) {
        if (joystickValue > 10 && joystickValue < -10) {
            position.x += 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || joystickValue < -10) { position.x -= SPEED * deltaTime; stateLook = LOOK_LEFT; stateMove = RUN; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || joystickValue > 10) { position.x += 1 + SPEED * deltaTime; stateLook = LOOK_RIGHT; stateMove = RUN; }
        else {
            stateMove = IDLE;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, 0)) { jump(); }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 2)) { isAttacking = true; }

    // Si la gâchette gauche est pressée ou que A est pressée OU si la gâchette droite est pressée ou que A est pressée
    if (((sf::Mouse::isButtonPressed(sf::Mouse::Right) || gachetteValue > 10) || (Keyboard::isKeyPressed(Keyboard::A) || gachetteValue < -10)) && isTakeDash && !isDashing && coolDownDash.getElapsedTime().asMilliseconds() >= 1500) {
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
        // Verification des gachettes (left = 10 & right = -10)
        gachetteValue = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

        joystickValue = sf::Joystick::getAxisPosition(0, sf::Joystick::X); // donne la poussée du joystick gauche sur l'axe X

    }

    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;
    
    //shape.setPosition(position);
    sprite.setPosition(position);

    if (sprite.getPosition().y < -20) {
        sprite.setPosition(position.x, position.y = 64);
    }
    if (sprite.getPosition().y > 1080) {
        sprite.setPosition(position.x, position.y = 1080);
    }
    if (sprite.getPosition().x < 0) {
        sprite.setPosition(position.x = 0, position.y);
    }
    if (sprite.getPosition().x > 1920) {
        sprite.setPosition(position.x = 1920, position.y);
    }
}

void Player::animationManager(float deltaTime) {
    switch (stateMove)
    {
    case RUN:
        animRunTimeDecr += deltaTime;
        anim_move.y = 0;
        if (animRunTimeDecr > 0.12f) {
            anim_move.x++;
            animRunTimeDecr = 0;
        }
        if (stateLook == LOOK_LEFT) {
            if (anim_move.x > 6) 
                anim_move.x = 1;
            sprite.setTextureRect(sf::IntRect(anim_move.x * 64, anim_move.y * 64, -64, 64));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_move.x > 5)
                anim_move.x = 0;
            sprite.setTextureRect(sf::IntRect(anim_move.x * 64, anim_move.y * 64, 64, 64));
        }
        break;
    case IDLE : 
        animIdleTimeDecr += deltaTime;
        anim_idle.y = 0;
        if (animIdleTimeDecr > 0.12f) {
            anim_idle.x++;
            animIdleTimeDecr = 0;
        }
        if (stateLook == LOOK_LEFT) {
            if (anim_idle.x > 8)
                anim_idle.x = 1;
            sprite.setTextureRect(sf::IntRect(anim_idle.x * 64, anim_idle.y * 64, -64, 64));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_idle.x > 7)
                anim_idle.x = 0;
            sprite.setTextureRect(sf::IntRect(anim_idle.x * 64, anim_idle.y * 64, 64, 64));
        }
        break;
    }
}

void Player::jump() {

    if (state == GROUNDED) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        state = JUMP;
        velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut pour sauter 
        jumpCount = 1;
        jumpClock.restart();
    }
    else if (jumpCount == 1 && jumpClock.getElapsedTime().asMilliseconds() >= 175 && state != GROUNDED) { // compteur permettant de savoir si on peut faire un deuxième saut
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
        sprite.setColor(Color::Blue);
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
    else {
        sprite.setColor(Color::White);
    }
}

void Player::collisionPlatform(RectangleShape& tile, float deltaTime) {
    if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds()) && tile.getPosition().y < position.y) { // si le perso se trouve sous la plateforme il ne la traverse pas 
        position.y = tile.getPosition().y + 40;
        velocity.y = gravity * deltaTime;
        state = NONE;
    }
    else if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds()) && tile.getPosition().y > position.y) { // collision de base 
        position.y = tile.getPosition().y - 64;
        velocity.y = 0;
        state = GROUNDED;
    }
}

void Player::collisionFloor(RectangleShape& tile) {
    if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds())) { // si le joueur entre en collision avec le sol alors il set sa position en haut du sol
        setPosPos(getPosPos().x, tile.getPosition().y - 64);
        velocity.y = 0;
        state = GROUNDED;
    }
    else if (tile.getPosition().y < getPosPos().y) { // s'il passe sous le sol
        setPosPos(getPosPos().x, tile.getPosition().y - 64);
    }
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

//bool Player::getIsJumping() {
//    return isJumping;
//}
//
//bool Player::setIsJumping(bool jump) {
//    isJumping = jump;
//    return isJumping;
//}
//
//bool Player::setIsGrounded(bool is)
//{
//    isGrounded = is;
//    return isGrounded;
//}
//
//bool Player::getIsGrounded()
//{
//    return isGrounded;
//}

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