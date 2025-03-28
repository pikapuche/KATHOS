#include "Boss.hpp"

Boss::Boss() : Entity(position.x, position.y) {
    textureIdle.loadFromFile("Assets/texture/Boss/boss-radioactiveV2.png");
    textureAttack.loadFromFile("Assets/texture/Boss/boss-radioactive_attackV2.png");
    sprite.setTexture(textureIdle);
    sprite.setScale(Vector2f(3, 3));
    speed = 150.f;
    velocity.y = 0;
    boxCol1 = 1;
    boxCol2 = 1;
    life = 250;
    lifeBar.setSize(Vector2f(life, 10.0f));
    lifeBar.setFillColor(Color::Green);
    rectBar.setSize(Vector2f(life, 10));
    rectBar.setFillColor(Color::Transparent);
    rectBar.setOutlineColor(Color::White);
    rectBar.setOutlineThickness(2);
    sprite.setOrigin(sprite.getLocalBounds().left / 2, sprite.getLocalBounds().top / 2);
    state = JUMP;
    directionState = LEFT;
}

void Boss::jump()
{
    if (state == GROUNDED) {
        state = JUMP;
        isJumping = true;
        velocity.y = -jumpForce;
    }
}

void::Boss::tired() {
    if (state == GROUNDED && state != JUMP) {
        isTired = true;
        coolDownTired.restart();
    }
}

void Boss::takeDamage(Player& player)
{
    if (life >= 167) {
        lifeBar.setFillColor(Color::Green);
    }
    else if (life <= 84) {
        lifeBar.setFillColor(Color::Red);
    }
    else if (life <= 167) {
        lifeBar.setFillColor(Color::Yellow);
    }
    if (player.getAttackShape().getGlobalBounds().intersects(sprite.getGlobalBounds()) && player.stateWeapon == player.SPAWN) {
        setLife(-1);
        lifeBar.setSize(Vector2f(life, 10));
    }
}

void Boss::doDamage(Player& player)
{
    if (sprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) && !player.getInvincible()) {
        player.setLife(-10);
        player.setInvincible(true);
        player.coolDownInvincible.restart();
    }
}

void Boss::movementManager(float pos, float pos2, float deltaTime) { // permet de gerer le mouvement de l'ennemi
    if (state == GROUNDED) {
        sprite.setTexture(textureIdle);
    }
    else if (state == JUMP) {
        sprite.setTexture(textureAttack);
    }

    if (!isJumping) {
        if (position.x < pos && directionState != RIGHT) { // faire en sorte qu'il ne puisse pas changer de direction pendant un saut
            directionState = RIGHT;
        }
        else if (position.x > pos2 && directionState != LEFT) {
            directionState = LEFT;
        }
    }

    if (!isTired)
    {
        if (directionState == RIGHT) {
            position.x += speed * deltaTime;
        }
        else {
            position.x -= speed * deltaTime;
        }
    }
    else if (isTired && coolDownTired.getElapsedTime().asSeconds() >= 3) {
        isTired = false;
    }

    if (state != GROUNDED) velocity.y += gravity * deltaTime;  // Appliquer la gravité
    else if (state == GROUNDED) velocity.y = 0;

    position.y += velocity.y * deltaTime;

    sprite.setPosition(position);
    detectionRect.setPosition(position);

    if (sprite.getPosition().x < 90) { // gauche de l'écran
        sprite.setPosition(position.x = 90, position.y);
    }
    if (sprite.getPosition().x > 1660) { // droite de l'écran
        sprite.setPosition(position.x = 1660, position.y);
    }
}

void Boss::animationManager(float deltaTime) {
    switch (state) {
    case GROUNDED:
        animDecrIdle += deltaTime;
        anim_idle.y = 0;
        if (animDecrIdle > 0.12f) {
            anim_idle.x++;
            animDecrIdle = 0;
        }
        if (directionState == LEFT) {
            if (anim_idle.x > 20)
                anim_idle.x = 1;
            sprite.setTextureRect(IntRect(anim_idle.x * 64, 0, -64, 64)); 
        }
        else if (directionState == RIGHT) {
            if (anim_idle.x > 19)
                anim_idle.x = 0;
            sprite.setTextureRect(IntRect(anim_idle.x * 64, 0, 64, 64));
        }
        break;
    case JUMP:
        animDecrAttack += deltaTime;
        anim_jump.y = 0;
        if (animDecrAttack > 0.12f) {
            anim_jump.x++;
            animDecrAttack = 0;
        }
        if (directionState == LEFT) {
            if (anim_jump.x > 6)
                anim_jump.x = 1;
            sprite.setTextureRect(IntRect(anim_jump.x * 64, anim_jump.y * 64, -64, 64));
        }
        else if (directionState == RIGHT) {
            if (anim_jump.x > 5)
                anim_jump.x = 0;
            sprite.setTextureRect(IntRect(anim_jump.x * 64, anim_jump.y * 64, 64, 64));
        }
        break;
    }
}

void Boss::update(float deltaTime, Player& player) {

    if (jumpClock.getElapsedTime().asSeconds() >= 1 && state == GROUNDED) {
        canJump = true;
    }

    if (canJump) {
        onestla = rand() % 10;
        canJump = false;
        jumpClock.restart();
    }

    //cout << onestla << endl;

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
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        tired();
        break;
    case 9:
        break;
    }

    if (state == GROUNDED) {
        isJumping = false;
    }

    movementManager(player.getSprite().getPosition().x, player.getSprite().getPosition().x, deltaTime);
    animationManager(deltaTime);
    lifeBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20);
    rectBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20);
    takeDamage(player);
    doDamage(player);
}

void Boss::draw(RenderWindow& window) {
    window.draw(detectionRect);
    window.draw(lifeBar);
    window.draw(rectBar);
    window.draw(sprite);
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