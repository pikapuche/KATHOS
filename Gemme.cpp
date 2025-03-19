#include "Gemme.hpp"

Gemme::Gemme(float _x, float _y, GemmeState state) : gemmeState(state) { 
	gemmeTexture.loadFromFile("Assets/gemme.png");
	gemmeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	gemmeSprite.setTexture(gemmeTexture);
	gemmeSprite.setPosition(Vector2f(_x,_y));

	switch (gemmeState) {
	case GemmeState::DASH:
		gemmeSprite.setColor(sf::Color::Green);
		break;
	case GemmeState::SPEED:
		//gemmeSprite.setColor(sf::Color(175, 175, 255, 100));
		gemmeSprite.setColor(sf::Color::Magenta);
		break;

	case GemmeState::DOUBLEJUMP:
		gemmeSprite.setColor(sf::Color::Yellow);
		break;
	}
}

void Gemme::animationGemme(float _deltaTime)
{
	animGemmeTime += _deltaTime;
	anim.y = 0;
	if (animGemmeTime > 0.12f) {
		gemmeSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	}
	if (animGemmeTime >= 0.24f) {
		animGemmeTime = 0;
		gemmeSprite.setTextureRect(sf::IntRect(0,0, 32, 32));
	}
}

void Gemme::interact(const std::shared_ptr<Player>& player)
{
	if (gemmeSprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
		if (gemmeState == GemmeState::DASH) {
			//cout << "TAKEN" << endl;
			player->setIsTakeDash(true);
			wasTaken = true;
		}
		else if (gemmeState == GemmeState::SPEED) {
			player->setIsTakeSpeed(true);
			wasTaken = true;
		}
		else if (gemmeState == GemmeState::DOUBLEJUMP) {
			player->setIsTakeJump(true);
			wasTaken = true;
		}
		else {
			cout << "Something arry" << endl;
		}
	}

}

void Gemme::updateGemme(float _deltaTime, const std::shared_ptr<Player>& player)
{
	animationGemme(_deltaTime); 
	interact(player);
};

bool Gemme::getGemTaken() {
	return wasTaken;
}