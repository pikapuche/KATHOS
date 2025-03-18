#include "Game.hpp"

void Game::removeDeadEnemies(Map& m) 
{ // avec chat gpt car j'y arrivais pas tant pis
    m.enemies.erase(remove_if(m.enemies.begin(), m.enemies.end(), [](const unique_ptr<Enemy>& enemy) { return enemy->getLife() == 0; }), m.enemies.end()); // Supprime les ennemis avec 0 PV
}

void Game::removeDeadBosses(Map& m)
{
    m.bosses.erase(remove_if(m.bosses.begin(), m.bosses.end(), [](const unique_ptr<Boss>& boss) { return boss->getLife() == 0; }), m.bosses.end()); // Supprime les boss avec 0 PV
}

//void Game::removeDeadBosses(Map& m)
//{
//    if (m.bosses.size() == 1 && m.bosses[0]->getLife() == 0) {
//        m.bosses.clear(); // Supprime directement le seul boss du vecteur
//    }
//    else {
//        m.bosses.erase(
//            remove_if(m.bosses.begin(), m.bosses.end(),
//                [](const unique_ptr<Boss>& boss) { return boss->getLife() == 0; }),
//            m.bosses.end()
//        );
//    }
//}

void Game::run()
{
    RenderWindow window(VideoMode(1920, 1080), "Kathos", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    MainScreen mainScreen;
    Interface overlay;
    mainScreen.initMenu(window);
    Map m;
    m.loadMap();

    Clock clock;
    overlay.initInterface();

    if (m.bossZone) {
        if (!music.openFromFile("Assets/Musiques/VSOLO musique boss16.wav")) {
            cout << "euuuuuuuuuuuuuu wtf la zic ?" << endl;
        }
        music.setLoop(true);
        music.setVolume(50.f);
        music.play();
    }

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

        if (mainScreen.getIsInMenu()) { //MENU
            mainScreen.updateMenu(window);
        }
        else { //JEU PRINCIPAL
            window.clear();

            if (overlay.getShouldRestart()) {
                m.resetAll();
                m.loadMap();
                overlay.resetRestartFlag();
            }
            if (!overlay.getIsPaused()) { // Only update game when not paused
                m.player->update(deltaTime);


                for (auto& enemy : m.enemies) {
                    enemy->update(deltaTime, *m.player);
                }

                for (auto& boss : m.bosses)
                    boss->update(deltaTime, *m.player);
            }

            for (auto& cloud : m.clouds) {
                cloud->update(deltaTime);
            }
            for (auto& gemme : m.gemmeSprites) {
                gemme->updateGemme(deltaTime, m.player);
            }
            removeDeadEnemies(m);
            removeDeadBosses(m);
            m.update(deltaTime);
            m.draw(window);

            overlay.updateInterface(window, *m.player); // Draw pause menu when paused
            if (!mainScreen.getIsInMenu())
                overlay.updateTimer(window); // ← THIS LINE UPDATES THE TIMER

            mainScreen.destroyAll();
        }
        // Affiche touter()
        window.display();
    }
}