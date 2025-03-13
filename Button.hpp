#pragma once
#include "SFML/Graphics.hpp"

enum class ButtonType {
    Play,
    Exit,
    Settings,
    Sound,
    Return,
    Resume,
    Restart
};

class Button {
private:
    Sprite button;
    Texture texture;
    Texture hoverTexture;
    ButtonType type;
    bool SettingsMenu;
    bool isHidden;

public:
    Button(float x, float y, float width, float height, ButtonType type, bool SettingsMenu, const string& texturePath, const string& texturePath2);
    void draw(RenderWindow& window);
    bool isHovered(RenderWindow& window);
    void setTexture(bool apply);
    ButtonType getType();  // Getter for type
    bool isInSettings();
	bool getisHidden();
	void setHidden(bool hidden);
    Vector2f getPosition();

    float getHeight();
	float getWidth();
};
