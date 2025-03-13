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

void Map::update() {
	collision();
}

void Map::collision(float deltaTime) {
	playerVector[0]->getSprite().getGlobalBounds();
	//for (auto& monde1 : monde1Vector )  Si touche la sortie donc clear pointeur

	/////// Player //////////
	//if (playerVector[0]->getSprite().getGlobalBounds().intersects(groundSprite->getGlobalBounds()) && groundSprite->getPosition().y < playerVector[0]->getPosPos().y) {}
	if (groundSprite->getGlobalBounds().intersects(playerVector[0]->getSprite().getGlobalBounds()) && groundSprite->getPosition().y < playerVector[0]->getPosPos().y) { // si le perso se trouve sous la plateforme il ne la traverse pas 
		playerVector[0]->setPosPos(playerVector[0]->getPosPos().x, groundSprite->getPosition().y + 32);
		playerVector[0]->setVelocity(playerVector[0]->getVelocity().x, playerVector[0]->getGravity() * deltaTime);
		playerVector[0]->state = playerVector[0]->State::NONE; 
	}
	else if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds()) && tile.getPosition().y > position.y) { // collision de base 
		position.y = tile.getPosition().y - 64;
		velocity.y = 0;
		state = GROUNDED;
	}
	if (tile.getGlobalBounds().intersects(sprite.getGlobalBounds())) { // si le joueur entre en collision avec le sol alors il set sa position en haut du sol
		setPosPos(getPosPos().x, tile.getPosition().y - 64);
		velocity.y = 0;
		state = GROUNDED;
	}
	else if (tile.getPosition().y < getPosPos().y) { // s'il passe sous le sol
		setPosPos(getPosPos().x, tile.getPosition().y - 64);
	}
}

void Map::monSwitch(ifstream& _Map, string _line, int _z) {
	
	while (getline(_Map, _line)) {
		for (int i = 0; i < _line.size(); i++) {
			switch (_line[i]) {
				cout << _line[i] << endl;
			case '1':
			{
				groundSprite = new Sprite;
				groundSprite->setTexture(groundGreenLeftTexture);
				groundSprite->setPosition({ (float)i * 32,(float)_z * 32 });
				groundGLVector.push_back(groundSprite);
				break;
			}
			case '2':
			{
				groundSprite = new Sprite;
				groundSprite->setTexture(groundGreenMidTexture);
				groundSprite->setPosition({ (float)i * 32,(float)_z * 32 });
				groundGMVector.push_back(groundSprite);
				break;
			}
			case '3':
			{
				groundSprite = new Sprite;
				groundSprite->setTexture(groundGreenRightTexture);
				groundSprite->setPosition({ (float)i * 32,(float)_z * 32 });
				groundGMVector.push_back(groundSprite);
				break;
			}
			case 'P':
			{
				Player* player = new Player;
				player->setPosPos((float)i * 32, (float)_z * 32);
				playerVector.push_back(player);
				break;
			}

			}
		}
		_z++;
	}
}

void Map::loadMap() {
	if (statePlaying == StatePlaying::Practice) {
		ifstream Map0("Assets/Map/Practice.txt");
		maps.push_back(&Map0);
		string line;
		float z = 0;

		for (auto& mapPractice : maps) {
			monSwitch(*mapPractice, line, z);
		}
	}
	if (statePlaying == StatePlaying::Monde1) {
		ifstream Map1("Assets/Map/Monde1.txt");
		maps.push_back(&Map1);
		string line;
		float z = 0;

		for (auto& mapMonde1 : maps) {
			monSwitch(*mapMonde1, line, z);
		}
	}
}

void Map::draw(RenderWindow& window) {
	for (auto& groundGL : groundGLVector) {
		window.draw(*groundGL);
	}
	for (auto& groundGM : groundGMVector) {
		window.draw(*groundGM);
	}
	for (auto& groundGR : groundGRVector) {
		window.draw(*groundGR);
	}
	for (auto& playerv : playerVector) {
		playerv->draw(window);
	}
}

void Map::gameOver(RenderWindow& window)
{
	if (isGameOver) {
		sf::RectangleShape gameOverScreen(sf::Vector2f(window.getSize().x, window.getSize().y));
		gameOverScreen.setFillColor(sf::Color(0, 0, 0, 150));
		window.draw(gameOverScreen);

		sf::Font font;
		if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
			cout << "Erreur chargement police !" << endl;
		}

		sf::Text gameOverText;
		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER");
		gameOverText.setCharacterSize(80);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setPosition((window.getSize().x - gameOverText.getGlobalBounds().width) / 2, (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

		window.draw(gameOverText);
		return;
	}
}
