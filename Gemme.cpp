#include "Gemme.hpp"

Gemme::Gemme() {}

void Gemme::animationGemme()
{
	gemmeTexture.loadFromFile("Assets/gemme.png");
	gemmeSprite.setTexture(gemmeTexture);

}

void Gemme::interact(Player& player)
{


}
void Gemme::updateGemme(float _x, float _y)
{
	animationGemme();
	position.x = _x;
	position.y= _y;
	gemmeSprite.setPosition(position);
};