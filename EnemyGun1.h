#pragma once
#include "Gun.h"

class EnemyGun1:public Gun
{
	sf::Time t2;
	sf::Clock c2;
	bool status;





public:
	EnemyGun1();
	void set_status(const bool a);
	//void recoil();
	void update(sf::Time deltaTime, sf::RenderWindow& newwindow, sf::Vector2f aim_direction, std::vector<TileSet*>& allAreas);

};

