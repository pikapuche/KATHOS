#include "Game.hpp"

void Game::removeDeadEnemies(Map& m) 
{ // avec chat gpt car j'y arrivais pas tant pis
    m.enemies.erase(remove_if(m.enemies.begin(), m.enemies.end(), [](const unique_ptr<Enemy>& enemy) { return enemy->getLife() == 0; }), m.enemies.end()); // Supprime les ennemis avec 0 PV
}

void Game::removeDeadBosses(Map& m)
{
    m.bosses.erase(remove_if(m.bosses.begin(), m.bosses.end(), [](const unique_ptr<Boss>& boss) { return boss->getLife() == 0; }), m.bosses.end()); // Supprime les boss avec 0 PV
}

void Game::initMusic()
{
    if (!music.openFromFile("Assets/Musiques/title.wav")) {
        std::cerr << "Failed to load title music!" << std::endl;
    }
    else {
        music.setLoop(true);
        music.setVolume(50.f);
    }

    if (!musicBoss.openFromFile("Assets/Musiques/VSOLO musique boss16.wav")) {
        cout << "euuuuuuuuuuuuuu wtf la zic ?" << endl;
    }
    musicBoss.setLoop(true);
    musicBoss.setVolume(5.f);
}
void Game::gameOver(RenderWindow& window, Interface& overlay)
{
    if (isGameOver) {
        musicBoss.stop();
        overlay.setWinCondition(true); //flemme de changer le nom pour l'instant 

        RectangleShape gameOverScreen(Vector2f(window.getSize().x, window.getSize().y));
        gameOverScreen.setFillColor(Color(0, 0, 0, 150));
        window.draw(gameOverScreen);

        Font font;
        if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
            cout << "Erreur chargement police !" << endl;
        }

        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(80);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setStyle(Text::Bold);
        gameOverText.setPosition((window.getSize().x - gameOverText.getGlobalBounds().width) / 2, (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

        window.draw(gameOverText);

        Time finalTime = overlay.getFinalTime();
        int minutes = static_cast<int>(finalTime.asSeconds()) / 60;
        int seconds = static_cast<int>(finalTime.asSeconds()) % 60;
        int milliseconds = static_cast<int>(finalTime.asMilliseconds() % 1000);

        Text timeText;
        timeText.setFont(font);
        timeText.setCharacterSize(60);
        timeText.setFillColor(Color::White);
        timeText.setString("Time: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds) + ":" + to_string(milliseconds));
        timeText.setPosition((window.getSize().x - timeText.getGlobalBounds().width) / 2, (window.getSize().y - timeText.getGlobalBounds().height) / 2 + 80);
        window.draw(timeText);
        return;
    }
}

void Game::Win(RenderWindow& window, Interface& overlay)
{
    if (isWin) {
        musicBoss.stop();
        overlay.setWinCondition(true);

        RectangleShape winScreen(Vector2f(window.getSize().x, window.getSize().y));
        winScreen.setFillColor(Color(0, 0, 0, 150));
        window.draw(winScreen);

        Font font;
        if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
            cout << "Erreur chargement police !" << endl;
        }

        Text winText;
        winText.setFont(font);
        winText.setString("WIN");
        winText.setCharacterSize(80);
        winText.setFillColor(Color::Yellow);
        winText.setStyle(Text::Bold);
        winText.setPosition((window.getSize().x - winText.getGlobalBounds().width) / 2, (window.getSize().y - winText.getGlobalBounds().height) / 2);

        window.draw(winText);

        Time finalTime = overlay.getFinalTime();
        int minutes = static_cast<int>(finalTime.asSeconds()) / 60;
        int seconds = static_cast<int>(finalTime.asSeconds()) % 60;
        int milliseconds = static_cast<int>(finalTime.asMilliseconds() % 1000);

        Text timeText;
        timeText.setFont(font);
        timeText.setCharacterSize(60);
        timeText.setFillColor(Color::White);
        timeText.setString("Time: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds) + ":" + to_string(milliseconds));
        timeText.setPosition((window.getSize().x - timeText.getGlobalBounds().width) / 2, (window.getSize().y - timeText.getGlobalBounds().height) / 2 + 80);
        window.draw(timeText);
        return;
    }
}

void Game::run()
{
    RenderWindow window(VideoMode(1920, 1080), "Kathos", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    MainScreen mainScreen(music);
    Interface overlay;
    Controller controller;
    mainScreen.initMenu(window);
    Map m;
    m.loadMap();
    initMusic();

    Clock clock;
    overlay.initInterface();

    while (window.isOpen()) {
        controller.detectControllerInput();
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
            else if (controller.getUsingController()) {
                if (!mainScreen.getIsInMenu() && sf::Joystick::isButtonPressed(0,7)) {
                    overlay.setIsPaused(true);
                }
            }
        }
        if (mainScreen.getIsInMenu()) { // MENU
            if (music.getStatus() == sf::SoundSource::Stopped) {
                music.play();
            }
            overlay.setGameStarted(false);
            mainScreen.updateMenu(window, controller);
        }
        else { //JEU PRINCIPAL
            if (!overlay.getGameStarted()) {
                overlay.setGameStarted(true);
                overlay.resetTime();  // Optionally reset the timer to 0 at the transition.
            }
            window.clear();

            if (overlay.getShouldRestart()) {
                m.clearMap();
                m.loadMap();
                overlay.resetRestartFlag();
                isWin = false;
                isGameOver = false;
            }
            for (auto& cloud : m.clouds) {
                cloud->collision(*m.player);
                cloud->update(deltaTime);
                cloud->draw(window);
            }
            if (!overlay.getIsPaused() && !isWin && !isGameOver) { // Only update game when not paused
                m.player->update(deltaTime);
                if (m.player->getLife() <= 0) isGameOver = true;

                for (auto& enemy : m.enemies) {
                    enemy->update(deltaTime, *m.player);
                }
                for (auto& boss : m.bosses) {
                    boss->update(deltaTime, *m.player);
                    if (boss->getLife() <= 0) 
                    {
                        isWin = true;
                    }
                }


            }

            for (auto& gemme : m.gemmeSprites) {
                gemme->updateGemme(deltaTime, m.player);
            }
            removeDeadEnemies(m);
            removeDeadBosses(m);
            m.update(deltaTime, window);
            m.draw(window);

//             overlay.updateInterface(window, *m.player, controller); // Draw pause menu when paused
//             if (!mainScreen.getIsInMenu()) {
            if (!isWin && !isGameOver)
            {
                if (m.mapBoss && count < 1) {
                    musicBoss.play();
                    count++;
                }
                overlay.updateInterface(window, *m.player); // Draw pause menu when paused
            }
            if (!mainScreen.getIsInMenu())
            {
                overlay.updateTimer(window); // ← THIS LINE UPDATES THE TIMER
                music.stop();
            }
            gameOver(window, overlay);
            Win(window, overlay);

            mainScreen.destroyAll();
        }
        
        // Affiche touter()
        window.display();
    }
}