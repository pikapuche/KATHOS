#include "Player.hpp"

Player::Player() : Entity(position.x, position.y) { // constructeur de base 
    DEBUG = true;
    velocity.y = 0; // Pas de mouvement vertical au depart
    attackShape.setSize(sf::Vector2f(75.f, 25.0f));
    attackShape.setFillColor(sf::Color::Red);
    textureSprint.loadFromFile("assets/texture/player/playerRunV2piskel.png");
    textureIdle.loadFromFile("assets/texture/player/playerIdleV2piskel.png");
    textureJump.loadFromFile("assets/texture/player/playerJump.png");
    textureAttack.loadFromFile("assets/texture/player/playerAttackV2piskel.png");
    sprite.setTexture(textureSprint);
    sprite.setTextureRect(IntRect(0, 0, 64, 64));
    boxCol1 = 35;
    boxCol2 = 58;
    life = 100;
    lifeBar.setSize(Vector2f(life, 10));
    lifeBar.setFillColor(Color::Green);
    rectBar.setSize(Vector2f(100, 10));
    rectBar.setFillColor(Color::Transparent);
    rectBar.setOutlineColor(Color::White);
    rectBar.setOutlineThickness(2);
}

void Player::movementManager(float deltaTime) { 

    if (stateMove == IDLE) {
        sprite.setTexture(textureIdle);
    }
    else if (stateMove == RUNNING) {
        sprite.setTexture(textureSprint);
    }
    else if (stateMove == JUMPING) {
        sprite.setTexture(textureJump);
    }
    else if (stateMove == ATTACKING) {
        sprite.setTexture(textureAttack);
    }

    if (!isDashing) {
        if (joystickValue > 10 && joystickValue < -10) {
            position.x += 0;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Q) || joystickValue < -10)
        { 
            position.x -= SPEED * deltaTime; stateLook = LOOK_LEFT; 
            if (state == GROUNDED) {
                stateMove = RUNNING;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::D) || joystickValue > 10)
        { 
            position.x += SPEED * deltaTime; stateLook = LOOK_RIGHT; 
            if (state == GROUNDED) {
                stateMove = RUNNING;
            }
        }
        else {
            if (state == GROUNDED) {
                stateMove = IDLE;
            }
        }
        if (isAttacking) {
            stateMove = ATTACKING;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isButtonPressed(0, 0)) { jump(); }

    if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 2)) && coolDownAttack.getElapsedTime().asSeconds() >= 0.7) { isAttacking = true; coolDownAttack.restart(); }

    // Si la gâchette gauche est pressée ou que A est pressée OU si la gâchette droite est pressée ou que A est pressée
    if (((Mouse::isButtonPressed(Mouse::Right) || gachetteValue > 10) || (Keyboard::isKeyPressed(Keyboard::A) || gachetteValue < -10)) && isTakeDash && !isDashing && coolDownDash.getElapsedTime().asMilliseconds() >= 1500) {
        isDashing = true;
        clock.restart();
    }

    if ((Keyboard::isKeyPressed(Keyboard::LShift) || Joystick::isButtonPressed(0, 5)) && isTakeSpeed) {
        SPEED = 600;
    }
    else {
        SPEED = 300;
    }

    //////////////////////////////  Manette  //////////////////////////////////

    if (Joystick::isConnected(0))
    {
        // Verification des gachettes (left = 10 & right = -10)
        gachetteValue = Joystick::getAxisPosition(0, Joystick::Z);

        joystickValue = Joystick::getAxisPosition(0, Joystick::X); // donne la poussée du joystick gauche sur l'axe X

    }

    velocity.y += gravity * deltaTime;  // Appliquer la gravité
    position.y += velocity.y * deltaTime;
    
    sprite.setPosition(position);

    if (sprite.getPosition().y < 0) { // haut de l'écran
        sprite.setPosition(position.x, position.y = 0);
    }
    if (sprite.getPosition().y > 1016) { // bas de l'écran 
        sprite.setPosition(position.x, position.y = 1016);
    }
    if (sprite.getPosition().x < 0) { // gauche de l'écran
        sprite.setPosition(position.x = 0, position.y);
    }
    if (sprite.getPosition().x > 1856) { // droite de l'écran
        sprite.setPosition(position.x = 1856, position.y);
    }

    if (stateLook == LOOK_LEFT) {
        attackShape.setPosition(position.x - 50, position.y + 20);
    }
    else {
        attackShape.setPosition(position.x + 37, position.y + 20);
    }
}

void Player::animationManager(float deltaTime) {
    switch (stateMove)
    {
    case RUNNING:
        animRunTimeDecr += deltaTime;
        anim_move.y = 0; // a retrouver sous forme de Vecteur2i dans Entity.hpp
        if (animRunTimeDecr > 0.12f) {
            anim_move.x++;
            animRunTimeDecr = 0;
        }
        if (stateLook == LOOK_LEFT) {

            if (anim_move.x > 6) 
                anim_move.x = 1;
            sprite.setTextureRect(IntRect(anim_move.x * 64, anim_move.y * 64, -64, 64));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_move.x > 5)
                anim_move.x = 0;
            sprite.setTextureRect(IntRect(anim_move.x * 64, anim_move.y * 64, 64, 64));
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
            sprite.setTextureRect(IntRect(anim_idle.x * 64, anim_idle.y * 64, -64, 64));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_idle.x > 7)
                anim_idle.x = 0;
            sprite.setTextureRect(IntRect(anim_idle.x * 64, anim_idle.y * 64, 64, 64));
        }
        break;
    case JUMPING :
        animJumpTimeDecr += deltaTime;
        anim_jump.y = 0; 
        if (animJumpTimeDecr > 0.12f) {
            anim_jump.x++;
            animJumpTimeDecr = 0;
        }
        if (stateLook == LOOK_LEFT) {
            if (anim_jump.x > 2)
                anim_jump.x = 1;
            sprite.setTextureRect(IntRect(anim_jump.x * 64, anim_jump.y * 64, -64, 64));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_jump.x > 1)
                anim_jump.x = 0;
            sprite.setTextureRect(IntRect(anim_jump.x * 64, anim_jump.y * 64, 64, 64));
        }
        break;
    case ATTACKING :
        animAttackTimeDecr += deltaTime;
        anim_attack.y = 0;
        if (animAttackTimeDecr > 0.10f) {
            anim_attack.x++;
            animAttackTimeDecr = 0;
        }
        if (stateLook == LOOK_LEFT) {
            if (anim_attack.x == 3) {
                stateWeapon = SPAWN;
            }
            if (anim_attack.x > 4) {
                anim_attack.x = 1;
                isAttacking = false;
                if (state != GROUNDED) {
                    stateMove = JUMPING;
                }
            }
            sprite.setTextureRect(IntRect(anim_attack.x * 64, 0, -64, 64));
        }
        else if (stateLook == LOOK_RIGHT) {
            if (anim_attack.x == 2) {
                stateWeapon = SPAWN;
            }
            if (anim_attack.x > 3) {
                anim_attack.x = 0;
                isAttacking = false;
                if (state != GROUNDED) {
                    stateMove = JUMPING;
                }
            }
            sprite.setTextureRect(IntRect(anim_attack.x * 64, 0, 64, 64));
        }
        break;
    }

    if (stateMove != ATTACKING) {
        stateWeapon = NONE;
    }
}

void Player::jump() {

    if (state == GROUNDED) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        state = JUMP;
        stateMove = JUMPING;
        velocity.y = -jumpForce;  // Appliquer une force initiale vers le haut pour sauter 
        jumpCount = 1;
        jumpClock.restart();
    }
    else if (jumpCount == 1 && jumpClock.getElapsedTime().asMilliseconds() >= 175 && state != GROUNDED && isTakeJump) { // compteur permettant de savoir si on peut faire un deuxième saut
        velocity.y = -jumpForce;
        jumpCount = 2;
    }
}

void Player::lifeGestion()
{
    if (life > 100) {
        lifeBar.setFillColor(Color::Green);
    }
    else if (life < 25) {
        lifeBar.setFillColor(Color::Red);
    }
    else if (life < 65) {
        lifeBar.setFillColor(Color::Yellow);
    }
    lifeBar.setSize(Vector2f(life, 10));
    lifeBar.setPosition(sprite.getPosition().x - 15, sprite.getPosition().y - 20);
    rectBar.setPosition(sprite.getPosition().x - 15, sprite.getPosition().y - 20);
}

void Player::takeDamage()
{
    if (invincible && coolDownInvincible.getElapsedTime().asSeconds() < 2) {
        sprite.setColor(Color::Red);
    }
    else if (invincible && coolDownInvincible.getElapsedTime().asSeconds() >= 2) {
        sprite.setColor(Color::White);
        invincible = false;
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

#pragma region Getteurs / Setteurs

Vector2f Player::getVelocity() {
    return velocity;
}

Vector2f Player::setVelocity(float veloX, float veloY) {
    velocity.x = veloX;
    velocity.y = veloY;
    return velocity;
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

bool Player::setIsTakeJump(bool jump)
{
    isTakeJump = jump;
    return isTakeJump;
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

bool Player::getInvincible()
{
    return invincible;
}

bool Player::setInvincible(bool inv)
{
    invincible = inv;
    return invincible;
}

RectangleShape Player::getAttackShape()
{
    return attackShape;
}

#pragma endregion Getteurs / Setteurs

void Player::update(float deltaTime) {
    movementManager(deltaTime);
    dash(deltaTime);
    animationManager(deltaTime);
    takeDamage();
    lifeGestion();
}

void Player::draw(RenderWindow& window) {
    window.draw(sprite);
    if (stateWeapon == SPAWN && DEBUG) window.draw(attackShape);
    window.draw(lifeBar);
    window.draw(rectBar);
}