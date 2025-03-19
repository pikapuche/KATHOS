#pragma once
#include "Map.hpp"
#include "Player.hpp"
#include "Gemme.hpp"
#include "MainScreen.hpp"
#include "Interface.hpp"

class Game {
public : 

	void removeDeadEnemies(Map& m);

	void removeDeadBosses(Map& m);

	void run();
};