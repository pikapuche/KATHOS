//#include "Ennemis.hpp"
//
//Enemy::Enemy(Vector2f wayOne, Vector2f wayTwo) : Entity(position.x, position.y)
//{
//	shape.setFillColor(Color::Magenta);
//	shape.setSize(Vector2f(32.0f, 32.0f));
//    circle.setRadius(50.0f);
//    circle.setPosition(position);
//    circle.setFillColor(Color::Red);
//    detectionRadius = 25.0f;
//    currentState = PATROL;
//    //circleOne.setFillColor(Color::Yellow);
//    //circleOne.setRadius(25.0f);
//    //circleTwo.setFillColor(Color::Blue);
//    //circleTwo.setRadius(25.0f);
//    //circleOne.setPosition(wayOne);
//    //circleTwo.setPosition(wayTwo);
//
//}
//
//bool Enemy::detectPlayer(Player& player)
//{
//    float distance = sqrt(pow(player.getPosPos().x - position.x, 2) + pow(player.getPosPos().y - position.y, 2));
//    return (distance < detectionRadius);
//}
//
//void Enemy::patrol(float deltaTime) // a bien restructurer et faire en sorte qu'il se déplace que sur l'axe x et pas sur le y avec le chemin a trouver 
//{
//    //if (position.x > circleOne.getPosition().x) {
//    //    position.x += SPEED * deltaTime;
//    //}
//    //else if (position.x > circleOne.getPosition().x && position.x < circleTwo.getPosition().x) {
//    //    position.x -= SPEED * deltaTime;
//    //}
//    //static int currentWaypoint = 0;
//    //static Vector2f waypoints[2] = { waypoint1, waypoint2 };
//    //Vector2f target = waypoints[currentWaypoint];
//    //Vector2f direction = target - position;
//    //float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
//
//    //if (distance < 5.0f) {
//    //    currentWaypoint = (currentWaypoint + 1) % 2;
//    //}
//    //else {
//    //    direction /= distance;
//    //    position += direction * SPEED;
//    //}
//}
//
////void Enemy::chase(Player& player)
////{
////    Vector2f direction = player.getPosPos() - position;
////    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
////
////    if (distance > 0) {
////        direction /= distance;
////        position += direction * 0.2f;
////    }
////    circle.setPosition(position);
////}
////
////void Enemy::search(Vector2f lastPlayerPos, float deltaTime)
////{
////    static float searchTimer = 0.0f;
////    static Vector2f searchDirection;
////
////    if (searchTimer == 0.0f) {
////        searchDirection = Vector2f(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
////        searchDirection /= sqrt(searchDirection.x * searchDirection.x + searchDirection.y * searchDirection.y);
////    }
////
////    searchTimer += deltaTime;
////    if (searchTimer < 10.0f) {
////        position += searchDirection * 5.f * deltaTime;
////    }
////    else {
////        searchTimer = 0.0f;
////        currentState = PATROL;
////    }
////
////    float distance = sqrt((lastPlayerPos.x - position.x) * (lastPlayerPos.x - position.x) + (lastPlayerPos.y - position.y) * (lastPlayerPos.y - position.y));
////    if (distance < detectionRadius) {
////        searchTimer = 0.0f;
////    }
////
////    circle.setPosition(position);
////}
//
//Vector2f Enemy::setPosPos(float x, float y)
//{
//    position.x = x;
//    position.y = y;
//    return position;
//}
//
//Vector2f Enemy::getPosPos()
//{
//    return position;
//}
//
//RectangleShape Enemy::getShape() {
//    return shape;
//}
//
//bool Enemy::setIsGrounded(bool is)
//{
//    isGrounded = is;
//    return isGrounded;
//}
//
//bool Enemy::getIsGrounded()
//{
//    return isGrounded;
//}
//
//void Enemy::update(float deltaTime)
//{
//}
//
//void Enemy::updateReal(float deltaTime, Player& player)
//{
//    if (isGrounded) {
//        velocity.y = 0;
//    }
//    else {
//        velocity.y += gravity * deltaTime;  // Appliquer la gravité
//    }
//    position.y += velocity.y * deltaTime;
//
//    switch (currentState) {
//    case PATROL:
//        patrol(deltaTime);
//        //if (detectPlayer(player)) currentState = CHASE;
//        break;
//    }
//    //case CHASE:
//    //    chase(player);
//    //    if (!detectPlayer(player)) {
//    //        currentState = SEARCH;
//    //    }
//    //    break;
//
//    //case SEARCH:
//    //    search(lastPlayerPosition, deltaTime);
//    //    break;
//    //}
//    shape.setPosition(position);
//}
//
//void Enemy::draw(RenderWindow& window)
//{
//    window.draw(shape);
//    window.draw(circleOne);
//    window.draw(circleTwo);
//}