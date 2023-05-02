#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "TextureClass.h"
#include "TileSet.h"
#include "HUD.h"
#include "EnemyGun1.h"

class Game {

private:
	TextureClass textureClass;

	//sf::Sprite test;

	sf::RenderWindow window;
	sf::Event event;
	Player player;
	sf::View view;

	HUD hud;

	sf::Sprite enemy; //remove later

	TileSet startingArea, startingAreaWall;
	TileSet SA_bridge, SA_bridgeWall;

	TileSet initialArea, initialAreaWall;
	TileSet IA_bridge, IA_bridgeWall;

	TileSet middleArea, middleAreaWall;
	TileSet MA_bridge, MA_bridgeWall;

	std::vector<TileSet*> allAreas;

	std::vector<bool> status;


public:
	Game();
	void run();
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

};