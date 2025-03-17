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

        window.clear();

        if (!overlay.getIsPaused()) { // Only update game when not paused
            for (auto& player : m.players) {
                player->update(deltaTime);

                for (auto& enemy : m.enemies) 
                enemy->update(deltaTime, *player);
                

                for(auto& boss : m.bosses)
                boss->update(deltaTime, *player);
            }

            for (auto& cloud : m.clouds) {
                cloud->update(deltaTime);
            }

            for (auto& gemme : m.gemmeSprites) {
                gemme->updateGemme(deltaTime);
            }

            m.update(deltaTime);
        }

        m.draw(window);

        if (overlay.getIsPaused()) {
            overlay.updateInterface(window); // Draw pause menu when paused
        }

        if (mainScreen.getIsInMenu()) {
            mainScreen.updateMenu(window);
        }
        else {
            mainScreen.destroyAll();
        }

        // Affiche tout
        window.display();
    }
}