#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
#include <math.h>
#include <cmath>
#include "TextureClass.h"
#include "TileSet.h"

using namespace sf;

class Gun {
	

public:
	float gunspeed;

	//bool leftclicked;
	//bool rightclicked;
	int recoil_count;
	//int reload_check;
	//int count;
	sf::Time t1;
	sf::Clock c1;
	int bullet_type;
	int bullet_type2;


	//sf::Time t2;
	//sf::Clock c2;

	
	//int capacity;
	//int Tcapacity;
	//int Total_bullets_fired;
	int bullet_count;
	//bool emptycheck;
	sf::Vector2f gunpos;
	sf::Vector2f mousepos;
	float dx;
	float dy;
	float rotation;
	sf::Vector2f aim_direction;
	sf::Vector2f aim_direction_normalized;
	//bool status;
	//bool check;

	std::vector<sf::Vector2f> DIRECTION;


	sf::Sprite sprite;//moved
	std::vector<Bullet*> bullet_vector;//moved
	Gun(int type, int type2);
	/*void handle_keyboard_input(sf::Keyboard::Key key, bool IsPressed);
	void handle_left_mouse_input(bool IsClicked);
	void handle_right_mouse_input(bool IsClicked);*/
	void update(sf::Time deltaTime, sf::RenderWindow& newwindow, sf::Vector2f aim_direction, std::vector<TileSet*>& allAreas);
	sf::Sprite& getsprite();
	//int getCapacity() const;
	std::vector<Bullet*>& getBullets();
	int getBulletCount() const;
	//void set_status(const bool a);
	int get_bullet_type() const;
	//bool isReloading() const;
	void Shoot(sf::Time deltaTime, std::vector<TileSet*>& allAreas) ;
	void move(sf::Time deltaTime, std::vector<TileSet*>& allAreas);
	void recoil();
	~Gun();

};