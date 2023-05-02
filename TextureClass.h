#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureClass {

private:
	std::map<std::string, std::unique_ptr<sf::Texture>> TextureMap;

public:
	TextureClass();
	void addTexture(const std::string, const std::string& filename);
	sf::Texture& retrieveTexture(const std::string);
	static TextureClass* get();

private:
	static TextureClass* instance;

};