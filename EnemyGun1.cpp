#include "EnemyGun1.h"
EnemyGun1::EnemyGun1():Gun(1,1)
{
	sprite.setTexture(TextureClass::get()->retrieveTexture("Enemy_Pistol"));
	sprite.setPosition(100, 100);

	status = true;
}
void EnemyGun1::set_status(const bool a)
{
	status = a;

}


void EnemyGun1::update(sf::Time deltaTime, sf::RenderWindow& newwindow, sf::Vector2f aim_direction, std::vector<TileSet*>& allAreas)
{
	if (status == true)
	{
		
		if (t2.asSeconds() >= 1.0)
		{

			recoil_count=1;
			Shoot(deltaTime, allAreas);
			move(deltaTime, allAreas);
			recoil();
			c2.restart();
		}
		
		t2 = c2.getElapsedTime();
	}




}