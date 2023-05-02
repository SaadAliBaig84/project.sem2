#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Player.h"
#include "TextureClass.h"
#include "TileSet.h"
#include "PlayerGun1.h"
#include "EnemyGun1.h"

class Player {

private:
	float health;
	int lives;
	bool damageEnabled;

	bool movingRight, movingLeft, movingUp, movingDown, dodging;
	bool pointingRight, pointingLeft, pointingUp, pointingDown, pointingUpRight, pointingUpLeft;
	bool pointingDownRight, pointingDownLeft;
	float angle, PlayerSpeed;
	int mouseCount;
	sf::Vector2i delta, windowCenter;
	sf::Vector2f aim_direction;

	sf::Vector2f sum;
	float idlePositionY;
	int movingCount, idleCount, dodgingCount, frames, deathCount;
	sf::Vector2i movingUpArray[6], movingDownArray[6], movingDownRightArray[6], movingUpRightArray[6];
	sf::Vector2i idleUpArray[6], idleDownArray[6], idleDownRightArray[6], idleUpRightArray[6];
	const sf::Vector2i dimensions, dimensions_reflected;
	sf::Vector2f handPosition, handLeft, handDown, handRight, handUp, handUpRight, handUpLeft;

	std::string file_path;
	sf::Texture texture, shadow;
	sf::Sprite sprite, sprite_shadow, sprite_hand;

	sf::Vector2f timed_movement, timed_view_movement;

	bool isShaking, isHealing;
	int shakeCount;
	sf::View originalView;

	bool isDead, gameOver;

	std::vector<bool> status;	//gameOver, reloading...

	int gunIndex;
	//Gun pistol, smg;
	PlayerGun1 pistol,smg;
	EnemyGun1 pistol2;
	std::vector<Gun*> allGuns;
	sf::Vector2f gunPosition;

public:
	Player();
	void setHealth(const float x);
	float getHealth() const;
	void setLives(const int x);
	int getLives() const;
	void playerKeyboardInput(sf::Keyboard::Key key, bool isPressed);
	void playerMouseInput(sf::RenderWindow& window);
	void playerClickInput(sf::Mouse::Button button, bool isPressed);
	void playerScrollInput(float delta);
	std::vector<bool> playerUpdate(sf::Time deltaTime, sf::RenderWindow& window, sf::View& view, sf::Sprite& enemy, std::vector<TileSet*>& allAreas);
	void playerMovingUpdate(sf::Vector2f& movement, sf::Vector2f& view_movement, sf::Time deltaTime);
	void playerIdleUpdate();
	bool isPointingUp() const;
	void playerRender(sf::RenderWindow& window);
	void takeDamage(int damage);
	sf::Sprite& getSprite();


};