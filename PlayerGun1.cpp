#include "PlayerGun1.h"

PlayerGun1::PlayerGun1(int capacity):Gun(2, 1)
{
	this->capacity = capacity;
	count = 0;
	recoil_count = 0;
	reload_check = false;
	leftclicked = false;
	rightclicked = false;
	Tcapacity = 40;
	Total_bullets_fired = 0;
	check = false;
	emptycheck = false;
	sprite.setTexture(TextureClass::get()->retrieveTexture("Player_Pistol"));
	sprite.setOrigin(25, 70);
}

void PlayerGun1::handle_keyboard_input(sf::Keyboard::Key key, bool IsPressed)
{

	if (key == sf::Keyboard::R)
	{
		//std::cout << "You are reloading!" << std::endl;
		if (bullet_type == 2)
		{
			if (bullet_vector.size() == 0)
			{
				std::cout << "Magazine at full capacity." << std::endl;
			}
			else if (Total_bullets_fired == Tcapacity)
			{
				std::cout << "Ammo finished." << std::endl;
			}
			else
			{
				check = true;
				std::cout << "***RELOADING***" << std::endl;//amendment
				c1.restart();//amendment
				reload_check++;
				for (int i = 0; i <= bullet_count; i++) {
					delete bullet_vector.at(i);
				}
				bullet_vector.clear();
				bullet_count = -1;
				count = 0;
				DIRECTION.clear();

			}

		}
		else
		{
			std::cout << "INVALID CALL" << std::endl;
		}
	}

}

void PlayerGun1::handle_left_mouse_input(bool IsClicked)
{
	leftclicked = IsClicked;
}

void PlayerGun1::handle_right_mouse_input(bool IsClicked)
{
	rightclicked = IsClicked;
}

int PlayerGun1::getCapacity() const {
	return capacity;
}


bool PlayerGun1::isReloading() const {
	return check;
}


void PlayerGun1::update(sf::Time deltaTime, sf::RenderWindow& newwindow, sf::Vector2f aim_direction, std::vector<TileSet*>& allAreas)
{
	Gun::update( deltaTime, newwindow, aim_direction, allAreas);
	if (c1.getElapsedTime().asSeconds() > 2)
	{
		check = false;
	}

	if (reload_check > 0)
	t1 = c1.getElapsedTime();
	if (leftclicked)
	{
		if ((t1.asSeconds() == 0.0 && reload_check == 0) || (t1.asSeconds() >= 2.0 && reload_check > 0))//amendment
		{//amendment
			leftclicked = false;

			recoil_count = 1;

			//Bullet* temp = new Bullet(bullet_type, bullet_type2);

			if (Total_bullets_fired < Tcapacity)
			{
				if (bullet_vector.size() < capacity) {
					std::cout << Total_bullets_fired << "/" << Tcapacity << std::endl;
					Total_bullets_fired++;

					Shoot(deltaTime, allAreas);

				}
			}


			recoil();

		}
		else
		{
			std::cout << "***RELOADING***" << std::endl;
		}
	}
	move(deltaTime, allAreas);

}

void PlayerGun1::recoil()
{
	if (bullet_vector.size() < capacity)
	{
		if (bullet_vector.size() == capacity)
			count++;

		std::cout << bullet_vector.size() << std::endl;

		if (Total_bullets_fired < Tcapacity)
		{
			Gun::recoil();
		}
	}


	//jugaad
	if (count > 0)
	{
		if (Total_bullets_fired < Tcapacity)
		{
			Gun::recoil();
		}
		count = 0;
	}
}
