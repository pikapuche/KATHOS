#include "Game.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

void Game::run()
{
    RenderWindow window(VideoMode(1920, 1080), "Kathos", Style::Fullscreen);
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
        Time deltaT = clock.restart();
        float deltaTime = deltaT.asSeconds();
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (mainScreen.getIsInMenu() && event.key.code == Keyboard::Escape) {
                window.close();
            }
            else if (!mainScreen.getIsInMenu() && event.key.code == Keyboard::Escape) {
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