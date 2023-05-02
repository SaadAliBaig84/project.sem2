#pragma once
//#include <iostream>
//#include <vector>
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include "Bullet.h"
//#include <math.h>
//#include <cmath>
//#include "TextureClass.h"
//#include "TileSet.h"
#include "Gun.h"

class PlayerGun1:public Gun
{
	bool leftclicked;
	bool rightclicked;
	//int recoil_count;
	int reload_check;
	int count;
	sf::Time t1;
	sf::Clock c1;
	int capacity;
	int Tcapacity;
	int Total_bullets_fired;
	bool emptycheck;
	bool check;

	public:
	PlayerGun1(int capacity);
	void handle_keyboard_input(sf::Keyboard::Key key, bool IsPressed);
	void handle_left_mouse_input(bool IsClicked);
	void handle_right_mouse_input(bool IsClicked);
	void update(sf::Time deltaTime, sf::RenderWindow& newwindow, sf::Vector2f aim_direction, std::vector<TileSet*>& allAreas);
	//int getBulletCount() const;
	bool isReloading() const;
	int getCapacity() const;
	void recoil();


};

