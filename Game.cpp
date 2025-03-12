#include "Game.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kathos", sf::Style::Fullscreen);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60); 

    Map map;
    MainScreen mainScreen;
    Interface overlay;
    mainScreen.initMenu(window);
    map.loadFromFile("assets/map/mapVSprite.txt");
    map.initAll();

    Clock clock;
    overlay.initInterface(); // Ensure the texture is loaded once

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

        if (mainScreen.getIsInMenu()) {
            mainScreen.updateMenu(window);
        }
        else {
            mainScreen.destroyAll();
            map.drawMap(window);

            for (auto& players : map.vector_player) {
                if (!overlay.getIsPaused()) {
                    players->update(deltaTime);
                    for(auto& enemies : map.vector_enemy)
                    map.collisionMap(*players, *enemies, deltaTime);
                }
                players->draw(window);
            }

            if (overlay.getIsPaused()) {
                overlay.updateInterface(window);
            }

            for (auto& gemmes : map.vector_gemme) {
                for (auto& players : map.vector_player) { // vector player dans la map pour pouvoir le gérer dans ses déplacements
                    gemmes->interact(*players);
                    gemmes->draw(window, *players);
                }
            }

            for (auto& ennemis : map.vector_enemy) {
                for (auto& players : map.vector_player) {
                    ennemis->updateReal(deltaTime, *players);
                }
                ennemis->draw(window);
            }
            window.display();
        }
    }
}
