#include "TileSet.h"

void TileSet::loadFloor(sf::Texture* texture, sf::Vector2f tileSize, int width, int height) {
	tex_floor = texture;
	setScale(3.f, 3.f);
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width * height * 4);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			sf::Vertex* quad = &vertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			quad[0].texCoords = sf::Vector2f(0, 0);
			quad[1].texCoords = sf::Vector2f(tileSize.x, 0);
			quad[2].texCoords = sf::Vector2f(tileSize.x, tileSize.y);
			quad[3].texCoords = sf::Vector2f(0, tileSize.y);
		}
	}

}

void TileSet::loadWall(sf::Texture* texture, sf::Vector2f tileSize, int width, int height, sf::Vector2i exceptions[], int exceptionCount) {
	tex_floor = texture;
	setScale(3.f, 3.f);
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(((width + height) * 2 - exceptionCount) * 4);

	int count = 0;
	bool exception = false;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
				//sf::Vertex* quad = &vertices[(i + j) * 4];
				exception = false;

				//std::cout << i << ", " << j << std::endl;
				for (int k = 0; k < exceptionCount; k++) {
					if (exceptions[k] == sf::Vector2i(i + 1, j + 1)) {
						exception = true;
					}
				}

				if (!exception) {
					sf::Vertex* quad = &vertices[++count * 4];

					quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
					quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
					quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
					quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

					quad[0].texCoords = sf::Vector2f(0, 0);
					quad[1].texCoords = sf::Vector2f(tileSize.x, 0);
					quad[2].texCoords = sf::Vector2f(tileSize.x, tileSize.y);
					quad[3].texCoords = sf::Vector2f(0, tileSize.y);
				}


			}
		}
	}

}


void TileSet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = tex_floor;
	target.draw(vertices, states);
}

sf::FloatRect TileSet::getGlobalBounds() const {
	return getTransform().transformRect(vertices.getBounds());
}