#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureClass.h"

class HUD {

private:
	sf::Vector2i health_sprite_size;
	std::vector<sf::Sprite> health_sprite_vector;

	sf::Sprite reload, reload_bg;

	float numOfHearts;
	bool proxy;

public:
	HUD();
	void hudUpdate(float health, sf::View& view, bool reloading);
	void hudRender(sf::RenderWindow& window);
	sf::Sprite& getHealthSprite();

};
