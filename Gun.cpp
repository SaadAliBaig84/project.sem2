#include "Gun.h"

Gun::Gun(int type, int type2)
{
	/*check = 0;*/
	bullet_type = type;
	bullet_type2 = type2;
	Bullet bullet(type, type2);
	gunspeed = 1;
	/*if (bullet_type == 1)
	{
		sprite.setTexture(TextureClass::get()->retrieveTexture("Enemy_Pistol"));
		sprite.setOrigin(25, 70);
	}
	else if (bullet_type == 2)
	{

		if (bullet_type2 == 1)
		{
			sprite.setTexture(TextureClass::get()->retrieveTexture("Player_Pistol"));
			sprite.setOrigin(25, 70);
		}

		if (bullet_type2 == 2)
		{
			sprite.setTexture(TextureClass::get()->retrieveTexture("SMG"));
			sprite.setOrigin(31, 72);
		}

	}*/
	bullet_count = -1;

	/*this->capacity = capacity;
	bullet_count = -1;*/

	/*sprite.setPosition(500, 450);

	leftclicked = false;
	rightclicked = false;
	
	
	reload_check = 0;

	emptycheck = false;
	Tcapacity = 40;
	Total_bullets_fired = 0;*/
	dx = 0.0;
	dy = 0.0;
	rotation = 0.0;
	recoil_count = 0;
	/*count = 0;
	status = 1;*/
}

sf::Sprite& Gun::getsprite()
{
	return sprite;
}

//void Gun::handle_keyboard_input(sf::Keyboard::Key key, bool IsPressed)
//{
//
//	if (key == sf::Keyboard::R)
//	{
//		std::cout << "You are reloading!" << std::endl;
//		if (bullet_type == 2)
//		{
//			if (bullet_vector.size() == 0)
//			{
//				std::cout << "Magazine at full capacity." << std::endl;
//			}
//			else if (Total_bullets_fired == Tcapacity)
//			{
//				std::cout << "Ammo finished." << std::endl;
//			}
//			else
//			{
//				check = true;
//				std::cout << "***RELOADING***" << std::endl;//amendment
//				c1.restart();//amendment
//				reload_check++;
//				for (int i = 0; i <= bullet_count; i++) {
//					delete bullet_vector.at(i);
//				}
//				bullet_vector.clear();
//				bullet_count = -1;
//				count = 0;
//				DIRECTION.clear();
//
//			}
//
//		}
//		else
//		{
//			std::cout << "INVALID CALL" << std::endl;
//		}
//	}
//
//}

//void Gun::set_status(const bool a)
//{
//	if (bullet_type == 2)
//		std::cout << "INVALID CALL" << std::endl;
//	else
//		status = a;
//}
//
//void Gun::handle_left_mouse_input(bool IsClicked)
//{
//	leftclicked = IsClicked;
//}
//
//void Gun::handle_right_mouse_input(bool IsClicked)
//{
//	rightclicked = IsClicked;
//}

void Gun::update(sf::Time deltaTime, sf::RenderWindow& newwindow, sf::Vector2f aim_direction, std::vector<TileSet*>& allAreas)
{

	


	aim_direction_normalized = aim_direction / (float)sqrt(pow(aim_direction.x, 2) + pow(aim_direction.y, 2));
	rotation = std::atan2f(aim_direction_normalized.y, aim_direction_normalized.x) * (180.f / ((float)std::atan(1) * 4));
	sprite.setRotation(rotation);

	if (rotation > 112 || rotation < -112)
	{
		sprite.setScale(0.2f, -0.2f);
	}
	else
	{
		sprite.setScale(0.2f, 0.2f);
	}


	//if (leftclicked)
	//{
	//	if (bullet_type == 2)
	//	{

	//		if ((t1.asSeconds() == 0.0 && reload_check == 0) || (t1.asSeconds() >= 2.0 && reload_check > 0))//amendment
	//		{//amendment
	//			leftclicked = false;

	//			recoil_count = 1;

	//			//Bullet* temp = new Bullet(bullet_type, bullet_type2);

	//			if (Total_bullets_fired < Tcapacity)
	//			{
	//				if (bullet_vector.size() < capacity) {
	//					std::cout << Total_bullets_fired << "/" << Tcapacity << std::endl;
	//					Total_bullets_fired++;

	//					shoot(deltaTime, allAreas);

	//				}
	//			}

	//			
	//			recoil();

	//		}
	//		else
	//		{
	//			std::cout << "***RELOADING***" << std::endl;
	//		}
	//	}

	//}


	//move(deltaTime, allAreas);

	//if (bullet_type == 1 && status == 1)
	//{
	//	if (t2.asSeconds() >= 1.0)
	//	{
	//		leftclicked = false;

	//		recoil_count = 1;
	//		shoot(deltaTime, allAreas);

	//		if (recoil_count >= 11) {
	//			if (sprite.getRotation() >= 345 && sprite.getRotation() < 360)
	//			{
	//				sprite.rotate(12.f);
	//			}
	//		}
	//		else if (recoil_count != 0)
	//		{
	//			recoil_count++;
	//			sprite.rotate(-6.f);
	//		}
	//		c2.restart();
	//	}
	//	t2 = c2.getElapsedTime();
	//}
}

void Gun::recoil()
{
	if (recoil_count >= 11) {
		if (sprite.getRotation() >= 345 && sprite.getRotation() < 360)
		{
			sprite.rotate(12.f);
		}
	}
	else if (recoil_count != 0)
	{
		recoil_count++;

		sprite.rotate(-6.f);
	}
}
void Gun::move(sf::Time deltaTime, std::vector<TileSet*>& allAreas)
{
	for (int i = 0; i <= bullet_count; i++) {
		if (bullet_vector.at(i)->getIsShot()) {
			bool contained = false;
			for (int j = 0; j < allAreas.size(); j++) {
				contained = contained || allAreas.at(j)->getGlobalBounds().contains(bullet_vector.at(i)->get_bullet_sprite().getPosition());
			}

			if (contained) {
				bullet_vector.at(i)->shoot(DIRECTION.at(i), deltaTime);
			}
			else {
				bullet_vector.at(i)->setIsShot(false);
			}
		}

	}
}
//
//void Gun::recoil()
//{
//	if (bullet_vector.size() < capacity)
//	{
//		if (bullet_vector.size() == capacity)
//			count++;
//
//		std::cout << bullet_vector.size() << std::endl;
//
//		if (Total_bullets_fired < Tcapacity)
//		{
//			if (recoil_count >= 11) {
//				if (sprite.getRotation() >= 345 && sprite.getRotation() < 360)
//				{
//					sprite.rotate(12.f);
//				}
//			}
//			else if (recoil_count != 0)
//			{
//				recoil_count++;
//
//				sprite.rotate(-6.f);
//			}
//
//
//		}
//	}
//
//
//	//jugaad
//	if (count > 0)
//	{
//		if (Total_bullets_fired < Tcapacity)
//		{
//			if (recoil_count >= 11) {
//				if (sprite.getRotation() >= 345 && sprite.getRotation() < 360)
//				{
//					sprite.rotate(12.f);
//				}
//			}
//			else if (recoil_count != 0)
//			{
//				recoil_count++;
//
//				sprite.rotate(-6.f);
//			}
//
//
//		}
//		count = 0;
//	}
//
//
//
//
//}
//int Gun::getCapacity() const {
//	return capacity;
//}
//
std::vector<Bullet*>& Gun::getBullets() {
	return bullet_vector;
}
//
int Gun::getBulletCount() const {
	return bullet_count;
}

int Gun::get_bullet_type() const
{
	return bullet_type;
}
//
//bool Gun::isReloading() const {
//	return check;
//}
//
void Gun::Shoot(sf::Time deltaTime, std::vector<TileSet*>& allAreas)  {
	
	
	Bullet* temp = new Bullet(bullet_type, bullet_type2);
	

	bullet_count++;

	DIRECTION.push_back(aim_direction_normalized);

	bullet_vector.push_back(temp);
	

	bullet_vector.at(bullet_count)->set_bullet_position(sprite.getPosition(), rotation);
	

	bullet_vector.at(bullet_count)->setIsShot(true);
	bullet_vector.at(bullet_count)->rotate_sprite(rotation);
	
	
}




Gun::~Gun() {
	for (int i = 0; i <= bullet_count; i++) {
		delete bullet_vector.at(i);
	}
}

