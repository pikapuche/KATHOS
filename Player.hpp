#include "Entity.hpp"

class Player : public Entity {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    RectangleShape shape;

    const float gravity = 981.0f;  // Gravité en pixels par seconde carrée (simulation)
    float SPEED = 200.0f;  // Vitesse de déplacement horizontal
    float jumpForce = 600.f;  // Force initiale du saut
    bool isJumping;

public:

    Player(float s, float jForce);

    void movementManager(float deltaTime);

    void jump();

    Vector2f getPosPos();

    Vector2f setPosPos(float(x), float(y));

    Vector2f getVelocity();

    Vector2f setVelocity(float veloX, float veloY);

    RectangleShape getShape();

    bool getIsJumping();

    bool setIsJumping(bool jump);

    float getJumpForce();

    float setJumpForce(float force);

    float getGravity();

    float getSPEED();

    void update(float deltaTime);

    void draw(RenderWindow& window);
};