#include "Game.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kathos", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    Map map;
    MainScreen mainScreen;
    Interface overlay;
    mainScreen.initMenu(window);
    map.loadFromFile("assets/map/mapV1.txt");
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
                    map.collisionMap(window, *players, deltaTime);
                }
                players->draw(window);
            }

            if (overlay.getIsPaused()) {
                overlay.updateInterface(window);
                if (overlay.getShouldRestart()) {
                    map.vector_player.clear();  // Clear old player instances
                    map.loadFromFile("assets/map/mapV1.txt"); // Reload map
                    map.initAll(); // Reset objects
                    overlay.resetRestartFlag(); // Reset the flag so it doesn't keep restarting

                }
                for (auto& players : map.vector_player) {
                    players->draw(window);
                }
            }

            window.display();
        }
    }
}
