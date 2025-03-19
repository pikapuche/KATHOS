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

//for (auto& enemy : m.enemies) { // parcours tout les nuages
//    auto it = std::find_if(m.enemies.begin(), m.enemies.end(), [&](const std::unique_ptr<Enemy>& enemyY) { // fais une référence a l'élément cloud
//        return enemyY.get() == enemy.get(); // Comparaison des adresses
//        });
//
//    if (it != m.enemies.end()) {
//        m.enemies.erase(it); // Supprime l'élément du vector
//        cout << "supp enemy" << endl;
//    }
//}