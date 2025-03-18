#include "Game.hpp"


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

                for (auto& enemy : m.enemies)
                    enemy->update(deltaTime, *m.player);

                for(auto& boss : m.bosses)
                boss->update(deltaTime, *m.player);
            }

            for (auto& cloud : m.clouds) {
                cloud->update(deltaTime);
            }
            for (auto& gemme : m.gemmeSprites) {
                gemme->updateGemme(deltaTime, m.player);
            }
            m.draw(window);
            m.update(deltaTime);
        

            m.draw(window);
           
            overlay.updateInterface(window, *m.player); // Draw pause menu when paused
            if (!mainScreen.getIsInMenu())
            overlay.updateTimer(window); // ← THIS LINE UPDATES THE TIMER

                overlay.updateInterface(window, *m.player); // Draw pause menu when paused
                overlay.updateTimer(window); // ← THIS LINE UPDATES THE TIMER

                mainScreen.destroyAll();


            }
        }
        // Affiche touter()
        window.display();
    }
}