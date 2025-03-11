#include "Game.hpp"

void Game::run()
{
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kathos", sf::Style::Fullscreen);
    window.setFramerateLimit(60); 

    Player player;
    Map* m = new Map();
    m->loadMap(player);

    Clock clock; // Horloge pour le deltaTime

    // Boucle principale
    while (window.isOpen()) {
        sf::Time deltaT = clock.restart(); // deltaTime permettant de synchroniser les déplacements et autres mouvements tous ensemble sur la même durée
        float deltaTime = deltaT.asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fenêtre
        }

        // Effacer la fenêtre
        window.clear();

        m->draw(window);

        //cout << deltaTime << endl;

        //for (auto& players : map.vector_player) { // vector player dans la map pour pouvoir le gérer dans ses déplacements
        //    players->update(deltaTime);
        //    players->draw(window);
        //    map.collisionMap(window, *players, deltaTime);
        //}


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
