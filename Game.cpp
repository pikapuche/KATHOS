#include "Game.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

//faire collision

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
        for (auto& playerv : m->playerVector) {
            playerv->update(deltaTime);
        }
        m->update();        
        m->draw(window);

        if (mainScreen.getIsInMenu()) {
            mainScreen.updateMenu(window);
        }
        else {
            mainScreen.destroyAll();

            if (overlay.getIsPaused()) {
                overlay.updateInterface(window);
            }
        }

        //for (auto& gemmes : map.vector_gemme) {
        //    for (auto& players : map.vector_player) { // vector player dans la map pour pouvoir le gérer dans ses déplacements
        //        gemmes->interact(*players);
        //    }
        //    gemmes->draw(window);
        //}

        // Affiche tout
        window.display(); 
    }
}
