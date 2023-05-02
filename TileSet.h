#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TileSet : public sf::Drawable, public sf::Transformable
{

private:
	sf::VertexArray vertices;
	sf::Texture* tex_floor, tex_wall;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	void loadFloor(sf::Texture* texture, sf::Vector2f tileSize, int width, int height);
	void loadWall(sf::Texture* texture, sf::Vector2f tileSize, int width, int height, sf::Vector2i exceptions[] = NULL, int exceptionCount = 0);
	sf::FloatRect getGlobalBounds() const;

};