#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include "TextureClass.h"

class Bullet
{
	sf::Texture TEXTURE;
	sf::Sprite bsprite;
	float maxspeed;
	sf::Vector2f curr_vel;
	bool Shot;

public:
	
	Bullet(int type, int type2);
	void set_maxspeed(float a);
	void set_bullet_position(sf::Vector2f, float a);
	void set_curr_vel(float a, float b);
	void setrotation(float a);
	void shoot(sf::Vector2f direction, sf::Time);
	bool getIsShot() const;
	void setIsShot(bool x);
	sf::Sprite& get_bullet_sprite();
	void rotate_sprite(float a);
	float get_maxspeed();
	sf::Vector2f get_bulletpos();
	sf::Transform transforming_vector;
	sf::Vector2f transformed_vector;


};