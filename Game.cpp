#include "Game.hpp"

void Game::run()
{
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test mini studio 2D");
    window.setFramerateLimit(60);

    Map map;
    //Grid grid;

    map.loadFromFile("C:\\Users\\quent\\OneDrive\\Documents\\Cours C++\\Mini studio\\mapV1.txt");
    map.initAll();

    //Player player(50, 500, 100.f, 50.f);

    Clock clock;

    // Boucle principale
    while (window.isOpen()) {
        sf::Time deltaT = clock.restart();
        float deltaTime = deltaT.asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fenêtre
        }

        // Effacer la fenêtre
        window.clear();

        map.drawMap(window);

        cout << deltaTime << endl;

        for (auto& players : map.vector_player) {
            players->update(deltaTime);
            players->draw(window);
            map.collisionMap(window, *players, deltaTime);
        }

        //player.update(deltaTime);

        //player.draw(window);

        // Afficher le contenu
        window.display();
    }
}
