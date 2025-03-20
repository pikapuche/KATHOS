#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include "Gemme.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

class Game {
public : 

	bool isGameOver = false;
	bool isWin = false;

	bool removeBoss = false;

	Music music;

	void removeDeadEnemies(Map& m);

	void removeDeadBosses(Map& m);

	void initMusic();

	void gameOver(RenderWindow& window);

	void Win(RenderWindow& window, Interface& overlay);

	void run();
};