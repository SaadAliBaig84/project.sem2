#include "Bullet.h"

Bullet::Bullet(int type, int type2)
{

	if (type == 1)
	{
		bsprite.setTexture(TextureClass::get()->retrieveTexture("Enemy_Pistol_Bullet"));
	}
	else if (type == 2)
	{
		if (type2 == 1)
		{
			bsprite.setTexture(TextureClass::get()->retrieveTexture("Player_Pistol_Bullet"));
		}

		if (type2 == 2)
		{
			bsprite.setTexture(TextureClass::get()->retrieveTexture("SMG_Bullet"));
		}
	}
	bsprite.setScale(0.7f, 0.7f);
	bsprite.setPosition(-100.f, -100.f);
	maxspeed = 0.3f;
	Shot = false;

}


void Bullet::set_maxspeed(float a)
{
	maxspeed = a;
}

float Bullet::get_maxspeed()
{
	return maxspeed;
}

void Bullet::set_curr_vel(float a, float b)
{
	curr_vel.x = a;
	curr_vel.y = b;

}

void Bullet::setrotation(float a)
{
	bsprite.setRotation(a);
}

void Bullet::rotate_sprite(float a)
{
	bsprite.rotate(a);
}

void Bullet::shoot(sf::Vector2f direction, sf::Time deltatime)
{
	bsprite.move(direction * ( 1/(deltatime.asSeconds()*2)) * maxspeed);
}

void Bullet::set_bullet_position(sf::Vector2f gunpos, float a)
{
	
	transforming_vector.rotate(a, gunpos);
	

	if (a <= -90 || a >= 90)
		transformed_vector = transforming_vector.transformPoint(gunpos + sf::Vector2f(50, 8));
	else
		transformed_vector = transforming_vector.transformPoint(gunpos + sf::Vector2f(50, -8));
	

	bsprite.setPosition(transformed_vector);
}

bool Bullet::getIsShot() const {
	return Shot;
}

void Bullet::setIsShot(const bool x) {
	Shot = x;
}

sf::Sprite& Bullet::get_bullet_sprite()
{
	return bsprite;
}

sf::Vector2f Bullet::get_bulletpos()
{
	return bsprite.getPosition();
}