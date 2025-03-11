#include "Map.hpp"

Map::Map() : statePlaying(StatePlaying::Practice) {
	groundYellowLeftTexture.loadFromFile("Assets/Map/groundYellowLeft.png");
	groundYellowMidTexture.loadFromFile("Assets/Map/groundYellowMid.png");
	groundYellowRightTexture.loadFromFile("Assets/Map/groundYellowRight.png");
	groundRedLeftTexture.loadFromFile("Assets/Map/groundRedLeft.png");
	groundRedMidTexture.loadFromFile("Assets/Map/groundRedMid.png");
	groundRedRightTexture.loadFromFile("Assets/Map/groundRedRight.png");
	groundGreenLeftTexture.loadFromFile("Assets/Map/groundGreenLeft.png");
	groundGreenMidTexture.loadFromFile("Assets/Map/groundGreenMid.png");
	groundGreenRightTexture.loadFromFile("Assets/Map/groundGreenRight.png");

}

void Map::update(Player& player) {
	collision(player);
}

void Map::collision(Player& player) {
	player.getShape().getGlobalBounds();
	//for (auto& monde1 : monde1Vector )  Si touche la sortie donc clear pointeur

<<<<<<< Updated upstream
    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            switch (vector_Map[i][j]) {
            case '=': // player
            {
                Player* players = new Player(100.f, 50.f);
                vector_player.push_back(players);
                for (auto& player : vector_player) { // set la position de départ du player
                    player->setPosPos(j * 40.f, i * 40.f);
                }
                break;
            }

            default:  tile.setFillColor(sf::Color::Black); break;
            }
            tile.setPosition(j * 40.f, i * 40.f);
        }
    }
=======
	// mettre les collisions

>>>>>>> Stashed changes
}

void Map::monSwitch(ifstream& _Map, string _line, int _z, Player& _player) {
	while (getline(_Map, _line)) {
		for (int i = 0; i < _line.size(); i++) {
			switch (_line[i]) {
				cout << _line[i] << endl;
			case '1': 
			{
				Sprite* gGL = new Sprite;
				gGL->setTexture(groundGreenLeftTexture);
				gGL->setPosition({ (float)i * 32,(float)_z * 32 });
				groundGLVector.push_back(gGL);
				break;
			}

<<<<<<< Updated upstream
    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            switch (vector_Map[i][j]) {
            case '!': { // sol
                tile.setFillColor(sf::Color::Red); // permet de set le sol de couleur rouge 
                break;
            }
=======
>>>>>>> Stashed changes


<<<<<<< Updated upstream
            default:  tile.setFillColor(sf::Color::Black); break;
            }
            tile.setPosition(j * 40.f, i * 40.f);
            window.draw(tile);
            if (winGame) {
                this_thread::sleep_for(std::chrono::seconds(3));
                window.close();
            }
        }
    }
=======
			}
		}
	}
>>>>>>> Stashed changes
}

void Map::loadMap(Player& player) {
	if (statePlaying == StatePlaying::Practice) {
		ifstream Map0("Assets/Map/Practice.txt");
		maps.push_back(&Map0);
		string line;
		float z = 0;

<<<<<<< Updated upstream
    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
        for (size_t j = 0; j < vector_Map[i].size(); j++) {
            switch (vector_Map[i][j]) {
            case '!': // plateformes
                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds()) && tile.getPosition().y > player.getPosPos().y) { // si le joueur entre en collision avec la plateforme mais qu'il est plus bas alors on set sa pos en dessous de la plateforme pour pas qu'il la traverse
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y + 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                else if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur entre en collision avec une plateforme alors il set sa position en haut de celle ci
                    cout << "collision" << endl;
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, 0);
                }
                if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur ne saute pas et qu'il n'est pas en collision alors il applique la gravité
                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                break;
            case '#': // sol 
                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur entre en collision avec une plateforme alors il set sa position en haut de celle ci
                    cout << "collision" << endl;
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
                    player.setIsJumping(false);
                    player.setVelocity(player.getVelocity().x, 0);
                }
                if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur ne saute pas et qu'il n'est pas en collision alors il applique la gravité
                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
                }
                if (tile.getPosition().y < player.getPosPos().y) {
                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 1 * 40.f);
                }
                break;
            default:  tile.setFillColor(sf::Color::Black); break;
            }
            tile.setPosition(j * 40.f, i * 40.f); // set la position des différentes tiles sur la map
        }
    }
}
=======
		for (auto& mapPractice : maps) {
			monSwitch(*mapPractice, line, z, player);
		}
	}

	if (statePlaying == StatePlaying::Monde1) {
		ifstream Map1("Assets/Map/Monde1.txt");
		maps.push_back(&Map1);
		string line;
		float z = 0;

		for (auto& mapMonde1 : maps) {
			monSwitch(*mapMonde1, line, z, player);
		}
	}


}

void Map::draw(RenderWindow& window) {
	for (auto& groundGL : groundGLVector) {
		window.draw(*groundGL);
	}



}







//Map::~Map() {
//    for (auto players : vector_player) {
//        delete players;
//    }
//    vector_player.clear();
//}
//
//bool Map::loadFromFile(string filename) {
//    ifstream file(filename);
//    if (!file) {
//        cerr << "Impossible d'ouvrir le fichier de la carte." << endl;
//        return false;
//    }
//
//    string line;
//    while (getline(file, line)) {
//        vector_Map.push_back(line);
//    }
//
//    if (!font.loadFromFile("Assets/Minecraft.ttf"))
//    {
//        cout << "error font" << endl << endl;
//    }
//}
//
//void Map::initAll() {
//    if (vector_Map.empty()) return;
//    sf::RectangleShape tile(sf::Vector2f(40, 40));
//
//    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
//        for (size_t j = 0; j < vector_Map[i].size(); j++) {
//            tile.setPosition(j * 40.f, i * 40.f);
//            switch (vector_Map[i][j]) {
//            case '=': // player
//            {
//                Player* players = new Player(100.f, 50.f);
//                vector_player.push_back(players);
//                for (auto& player : vector_player) { // set la position de départ du player
//                    player->setPosPos(j * 40.f, i * 40.f);
//                }
//                break;
//            }
//            case '*': 
//            {
//                Gemme* gemmes = new Gemme(100.0f, 50.0f);
//                vector_gemme.push_back(gemmes);
//                for (auto& gemme : vector_gemme) { // set la position de départ du player
//                    gemme->setPosition(j * 40.f, i * 40.f);
//                }
//                break;
//            }
//
//            default:  tile.setFillColor(sf::Color::Black); break;
//            }
//        }
//    }
//}
//
//void Map::drawMap(sf::RenderWindow& window) {
//    if (vector_Map.empty()) return;
//    sf::RectangleShape tile(sf::Vector2f(40, 40));
//
//    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map
//        for (size_t j = 0; j < vector_Map[i].size(); j++) {
//            tile.setPosition(j * 40.f, i * 40.f);
//            switch (vector_Map[i][j]) {
//            case '!': { // sol
//                tile.setFillColor(sf::Color::Red); // permet de set le sol de couleur rouge 
//                break;
//            }
//
//            case '#': {
//                tile.setFillColor(sf::Color::Cyan);
//                break;
//            }
//
//            default:  tile.setFillColor(sf::Color::Black); break;
//            }
//            window.draw(tile);
//        }
//    }
//}
//
//void Map::collisionMap(sf::RenderWindow& window, Player& player, float deltaTime) {
//    if (vector_Map.empty()) return;
//    sf::RectangleShape tile(sf::Vector2f(40, 40));
//
//    for (size_t i = 0; i < vector_Map.size(); i++) { // gros code qui permet de parcourir la map 
//        for (size_t j = 0; j < vector_Map[i].size(); j++) {
//            tile.setPosition(j * 40.f, i * 40.f); // set la position des différentes tiles sur la map
//            switch (vector_Map[i][j]) {
//            case '!': // plateformes
//                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds()) && tile.getPosition().y > player.getPosPos().y) { // si le joueur entre en collision avec la plateforme mais qu'il est plus bas alors on set sa pos en dessous de la plateforme pour pas qu'il la traverse
//                    player.setPosPos(player.getPosPos().x, tile.getPosition().y + 40);
//                    player.setIsJumping(true);
//                }
//                else if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds()) && tile.getPosition().y < player.getPosPos().y) { // si le joueur entre en collision avec une plateforme alors il set sa position en haut de celle ci
//                    cout << "collision plateforme" << endl;
//                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
//                    player.setIsJumping(false);
//                    player.setIsGrounded(true);
//                    player.setJumpCount(0);
//                    player.setVelocity(player.getVelocity().x, 0);
//                }
//                else if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur ne saute pas et qu'il n'est pas en collision alors il applique la gravité
//                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
//                }
//                break;
//            case '#': // sol 
//                if (tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur entre en collision avec le sol alors il set sa position en haut du sol
//                    cout << "collision sol" << endl;
//                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
//                    player.setIsJumping(false);
//                    player.setIsGrounded(true);
//                    player.setJumpCount(0);
//                    player.setVelocity(player.getVelocity().x, 0);
//                }
//                if (!player.getIsJumping() && !tile.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) { // si le joueur ne saute pas et qu'il n'est pas en collision alors il applique la gravité
//                    player.setVelocity(player.getVelocity().x, player.getJumpForce() * deltaTime * 18);
//                }
//                if (tile.getPosition().y < player.getPosPos().y) {
//                    player.setPosPos(player.getPosPos().x, tile.getPosition().y - 40);
//                }
//                break;
//            default:  tile.setFillColor(sf::Color::Black); break;
//            }
//        }
//    }
//}
>>>>>>> Stashed changes
