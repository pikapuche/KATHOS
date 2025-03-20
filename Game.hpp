#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include "Gemme.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"
#include "controllerManager.hpp"

class Game {
public : 

	int count = 0;

	bool isGameOver = false;
	bool isWin = false;

	bool removeBoss = false;

	Music music;
	Music musicBoss;

	void removeDeadEnemies(Map& m);

	void removeDeadBosses(Map& m);

	void initMusic();

	void gameOver(RenderWindow& window, Interface& overlay, Controller& controller);

	void Win(RenderWindow& window, Interface& overlay, Controller& controller);

	void run();
};