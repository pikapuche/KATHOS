#include "Game.hpp"

void Game::run()
{
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kathos", sf::Style::Fullscreen);
    window.setFramerateLimit(60); 

    Map map;

    map.loadFromFile("assets/map/mapBoss.txt"); // fichier de la map
    map.initAll();

    Clock clock; // Horloge pour le deltaTime

    // Boucle principale
    while (window.isOpen()) {
        sf::Time deltaT = clock.restart(); // deltaTime permettant de synchroniser les déplacements et autres mouvements tous ensemble sur la même durée
        float deltaTime = deltaT.asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close(); // Fermer la fenêtre
        }

        // Effacer la fenêtre
        window.clear();

        map.update(deltaTime);
        map.drawMap(window); // draw la map

        //cout << deltaTime << endl;

        for (auto& players : map.vector_player) { // vector player dans la map pour pouvoir le gérer dans ses déplacements
            players->update(deltaTime);
            players->draw(window);
            map.collisionMap(window, *players, deltaTime);
        }
        for (auto& bosses : map.vector_boss) { // vector boss dans la map pour pouvoir le gérer dans ses déplacements
            bosses->update(deltaTime);
            bosses->draw(window);
        }
        for (auto& nuages : map.vector_nuage) {
            nuages->update(deltaTime);
            nuages->draw(window);
        }

        // Affiche tout
        window.display();
    }
}