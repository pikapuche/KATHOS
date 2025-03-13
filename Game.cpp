#include "Game.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kathos", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    MainScreen mainScreen;
    Interface overlay;
    mainScreen.initMenu(window);
    Map* m = new Map();
    m->loadMap();

    Clock clock;
    overlay.initInterface();

    while (window.isOpen()) {
        sf::Time deltaT = clock.restart();
        float deltaTime = deltaT.asSeconds();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (mainScreen.getIsInMenu() && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (!mainScreen.getIsInMenu() && event.key.code == sf::Keyboard::Escape) {
                overlay.setIsPaused(true);
            }
        }

        window.clear();
        for (auto& playerv : m->playerVector) {
            playerv->update(deltaTime);
        }
        for (auto& bossrv : m->bossVector) {
            bossrv->update(deltaTime);
            bossrv->checkCollision(1920, 1080);
        }
        m->update();
        m->draw(window);

        window.display();
    }
}