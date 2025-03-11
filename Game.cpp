#include "Game.hpp"

void Game::run()
{
    // Cr�ation de la fen�tre
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kathos", sf::Style::Fullscreen);
    window.setFramerateLimit(60); 

    Map map;

    map.loadFromFile("assets/map/mapV1.txt"); // fichier de la map
    map.initAll();

    Clock clock; // Horloge pour le deltaTime

    // Boucle principale
    while (window.isOpen()) {
        sf::Time deltaT = clock.restart(); // deltaTime permettant de synchroniser les d�placements et autres mouvements tous ensemble sur la m�me dur�e
        float deltaTime = deltaT.asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fen�tre
        }

        // Effacer la fen�tre
        window.clear();

        map.drawMap(window); // draw la map

        //cout << deltaTime << endl;

        for (auto& players : map.vector_player) { // vector player dans la map pour pouvoir le g�rer dans ses d�placements
            players->update(deltaTime);
            players->draw(window);
            map.collisionMap(window, *players, deltaTime);
        }

        for (auto& gemmes : map.vector_gemme) {
            for (auto& players : map.vector_player) { // vector player dans la map pour pouvoir le g�rer dans ses d�placements
                gemmes->interact(*players);
                gemmes->draw(window, *players);
            }
        }

        // Affiche tout
        window.display();
    }
}
