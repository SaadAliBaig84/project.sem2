#include "Game.h"

Player::Player() : pistol(20), smg(20) {

	health = 4.f;
	lives = 3;
	damageEnabled = true;

	aim_direction = sf::Vector2f(0, 0);

	angle = 0, frames = 1, shakeCount = 0;
	movingDown = movingLeft = movingRight = movingUp = dodging = isShaking = false;
	pointingLeft = pointingRight = pointingUp = pointingUpLeft = pointingUpRight = pointingDownRight = pointingDownLeft = false;
	pointingDown = true;

	isDead = gameOver = false;

	PlayerSpeed = 200;

	mouseCount = 0;
	movingCount = idleCount = dodgingCount = deathCount = -1;

	sum = sf::Vector2f(0, 0);

	file_path = "Texture/Player/";

	sprite.setTexture(TextureClass::get()->retrieveTexture("playerDO_"));
	sprite.setPosition(450, 330);

	idlePositionY = sprite.getPosition().y + 66;

	handLeft = sf::Vector2f(45 * -0.25f, 70 * 0.63f);
	handDown = sf::Vector2f(51 * 0.73f, 66 * 0.63f);
	handRight = sf::Vector2f(45 * 0.75f, 70 * 0.62f);
	handUp = sf::Vector2f(51 * 0.73f, 66 * 0.6f);
	handUpRight = sf::Vector2f(45 * 0.79f, 64 * 0.64f);
	handUpLeft = sf::Vector2f(45 * -0.27f, 64 * 0.64f);
	handPosition = handDown;

	aim_direction = sf::Vector2f(1, 1);		//so that the gun appears as soon as game starts

	sprite_hand.setTexture(TextureClass::get()->retrieveTexture("playerHand"));
	sprite_hand.setPosition(handPosition);
	sprite_hand.setScale(1.05f, 1.05f);

	sprite_shadow.setTexture(TextureClass::get()->retrieveTexture("playerShadow"));
	sprite_shadow.setPosition(sprite.getPosition().x + 3, sprite.getPosition().y + 60);
	sprite_shadow.setScale(2.6f, 2.6f);

	status.push_back(gameOver);
	status.push_back(pistol.isReloading());

	gunIndex = 0;
	allGuns.push_back(&pistol);
	allGuns.push_back(&smg);

}

void Player::setHealth(const float x) {
	health = x;
}

float Player::getHealth() const {
	return health;
}

void Player::setLives(const int x) {
	lives = x;
}

int Player::getLives() const {
	return lives;
}

void Player::playerKeyboardInput(sf::Keyboard::Key key, bool isPressed) {

	if (key == sf::Keyboard::D) {
		movingRight = isPressed;
	}
	else if (key == sf::Keyboard::A) {
		movingLeft = isPressed;
	}

	if (key == sf::Keyboard::W) {
		movingUp = isPressed;
	}
	else if (key == sf::Keyboard::S) {
		movingDown = isPressed;
	}

	if (key == sf::Keyboard::LShift) {
		dodging = true;
		damageEnabled = false;
	}

	pistol.handle_keyboard_input(key, isPressed);

	if (key == sf::Keyboard::T) {		//remove
		isShaking = isPressed;
	}

	if (key == sf::Keyboard::Y) {
		isHealing = isPressed;
	}

}

void Player::playerScrollInput(float delta) {

	gunIndex += int(delta);

	if (gunIndex < 0) {
		gunIndex = allGuns.size() + gunIndex;
	}
	else if (gunIndex > allGuns.size()) {
		gunIndex = 0;
	}

}

void Player::playerMouseInput(sf::RenderWindow& window) {

	windowCenter = sf::Vector2i((window.getSize() / 2u));

	if ((sf::Mouse::getPosition(window).x != windowCenter.x || sf::Mouse::getPosition(window).y != windowCenter.y)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		delta += mousePosition - windowCenter;
		sf::Mouse::setPosition(windowCenter, window);

		mouseCount++;

		if (dodging || isDead) {
			mouseCount = 0;
		}
		else if (mouseCount == 6) {
			mouseCount = 0;

			idleCount = -1;

			pointingLeft = pointingRight = pointingUp = pointingUpLeft = pointingUpRight = pointingDown = pointingDownLeft = pointingDownRight = false;

			angle = atan2f(-(float)delta.y, (float)delta.x);
			angle = angle * 180.f * (7.f / 22.f);

			if (angle > 12.5 && angle <= 67.5) {
				pointingUpRight = true;
			}
			else if (angle > -67.5 && angle <= 12.5) {
				pointingRight = true;
				if (angle > -67.5 && angle <= -27.5) {
					pointingDownRight = true;
				}
			}
			else if (angle <= -67.5 && angle > -112.5) {
				pointingDown = true;
			}
			else if ((angle <= -112.5 && angle > -180) || (angle < 180 && angle > 167.5)) {
				pointingLeft = true;
				if (angle > -152.5 && angle < -112.5) {
					pointingDownLeft = true;
				}
			}
			else if (angle <= 167.5 && angle > 112.5) {
				pointingUpLeft = true;
			}
			else if (angle <= 122.5 && angle > 67.5) {
				pointingUp = true;
			}
			else if (angle == 180 || angle == -180) {
				pointingLeft = true;
			}

			aim_direction = sf::Vector2f(float(delta.x), float(delta.y));
			delta = sf::Vector2i(0, 0);
		}
	}
}

void Player::playerClickInput(sf::Mouse::Button button, bool isPressed) {

	if (button == sf::Mouse::Left) {
		pistol.handle_left_mouse_input(isPressed);
	}
	else if (button == sf::Mouse::Right) {
		pistol.handle_right_mouse_input(isPressed);
	}

}

std::vector<bool> Player::playerUpdate(sf::Time deltaTime, sf::RenderWindow& window, sf::View& view, sf::Sprite& enemy, std::vector<TileSet*>& allAreas) {
	
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f view_movement(0.f, 0.f);

	for (int i = 0; i <= pistol.getBulletCount(); i++) {
		if (pistol.getBullets().at(i)->get_bullet_sprite().getGlobalBounds().intersects(enemy.getGlobalBounds()) && pistol.getBullets().at(i)->getIsShot()) {
			pistol.getBullets().at(i)->setIsShot(false);
			std::cout << "shott" << std::endl;
		}
	}

	if (isShaking) {
		health -= 0.5;
		isShaking = false;
	}
	else if (isHealing) {
		health += 0.5;
		isHealing = false;
	}

	if (health <= 0) {
		isDead = true;
	}

	if (isDead) {

		if ((++deathCount / 7) == 9) {
			std::cout << "Game OVER!" << std::endl;
			isDead = false;
			gameOver = true;
			deathCount = 0;
			health = 4.f;
			sprite.setScale(1, 1);
		}
		else {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerDeath_DE_" + std::to_string(deathCount / 7)));
			if (pointingLeft || pointingDownLeft) {
				sprite.setTextureRect(sf::IntRect(sprite.getTexture()->getSize().x, 0, sprite.getTexture()->getSize().x * -1, sprite.getTexture()->getSize().y));
			}
			else {
				sprite.setTextureRect(sf::IntRect(0, 0, sprite.getTexture()->getSize().x, sprite.getTexture()->getSize().y));
			}
			sprite.setScale(3.2f, 3.2f);
		}

	}

	if (gameOver) {
		//std::cout << "GAME OVER!\n";
	}
	///isDead = false;

	//if (isShaking) {
	//	if (shakeCount == 0) {
	//		originalView = window.getView();
	//	}
	//	view_movement += sf::Vector2f(rand() * -1 * (shakeCount + 1) % 500, rand() * -1 * (shakeCount + 1) % 500);
	//	//window.setPosition(originalWindowPos + sf::Vector2i(rand() * -1 * (shakeCount+1) % 25, rand() * -1 * (shakeCount + 1) % 25));
	//	//window.setPosition(sf::Vector2i(100 + rand() % 25, 100 + rand() % 25));
	//	if (shakeCount++ == 5) {
	//		//window.setPosition(originalWindowPos);
	//		window.setView(originalView);
	//		shakeCount = 0;
	//		isShaking = false;
	//	}
	//}

	if (!dodging && !isDead) {
		if (movingDown) {
			movement.y += PlayerSpeed;
		}
		else if (movingUp) {
			movement.y -= PlayerSpeed;
		}

		if (movingRight) {
			movement.x += PlayerSpeed;
		}
		else if (movingLeft) {
			movement.x -= PlayerSpeed;
		}
	}

	float magnitude = sqrtf(powf(movement.x, 2.0) + powf(movement.y, 2.0));

	if ((magnitude || dodging) && !isDead) {
		playerMovingUpdate(movement, view_movement, deltaTime);
	}
	else if (!isDead) {
		playerIdleUpdate();
	}

	sf::Vector2f timed_movement = movement * deltaTime.asSeconds();
	sf::Vector2f timed_view_movement = view_movement * deltaTime.asSeconds();
	timed_view_movement += timed_movement;

	if (enemy.getGlobalBounds().intersects(sf::FloatRect(timed_movement.x + sprite.getGlobalBounds().left, timed_movement.y + sprite.getGlobalBounds().top, timed_movement.x + sprite.getGlobalBounds().width, timed_movement.y + sprite.getGlobalBounds().height))) {
		timed_movement *= 0.f;
		timed_view_movement *= 0.f;
	}

	bool player_contained = false, contained_UL = false, contained_UR = false, contained_DL = false, contained_DR = false;
	bool bullet_contained = false;
	sf::Vector2f playerPos = sprite.getPosition();

	for (int i = 0; i < allAreas.size(); i++) {
		contained_UL = contained_UL || allAreas[i]->getGlobalBounds().contains(playerPos + timed_movement);
		contained_UR = contained_UR || allAreas[i]->getGlobalBounds().contains(playerPos + timed_movement + sf::Vector2f(48, 0));
		contained_DR = contained_DR || allAreas[i]->getGlobalBounds().contains(playerPos + timed_movement + sf::Vector2f(48, 70));
		contained_DL = contained_DL || allAreas[i]->getGlobalBounds().contains(playerPos + timed_movement + sf::Vector2f(0, 70));
	}
	player_contained = contained_UL && contained_UR && contained_DR && contained_DL;

	if (!player_contained) {
		timed_movement = timed_view_movement = sf::Vector2f(0, 0);
	}

	if (!dodging) {
		pistol.update(deltaTime, window, aim_direction, allAreas);	//changed
		pistol2.update(deltaTime, window, aim_direction, allAreas);
	}

	if (pistol.isReloading()) {
		status.at(1) = 1;
	}
	else {
		status.at(1) = 0;
	}

	sprite.move(timed_movement);
	sprite_shadow.move(timed_movement);
	sprite_hand.move(timed_movement);
	view.move(timed_view_movement);
	sprite_hand.setPosition(sprite.getPosition() + handPosition);
	pistol.getsprite().setPosition(sprite_hand.getPosition() + sf::Vector2f(sprite_hand.getTexture()->getSize().x / 2.f, sprite_hand.getTexture()->getSize().y / 2.f) + sf::Vector2f(3.f, -3.f));

	return status;
}


void Player::playerMovingUpdate(sf::Vector2f& movement, sf::Vector2f& view_movement, sf::Time deltaTime) {

	idleCount = 0;
	if (!dodging) {
		if (pointingDown) {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerDO_" + std::to_string(++movingCount / 7 % 6)));
			sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
			sprite_shadow.setPosition(sprite.getPosition().x + 5, sprite.getPosition().y + 56);
			handPosition = handDown + sf::Vector2f(2.f, 0.f);
		}
		else if (pointingUp) {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerUO_" + std::to_string(++movingCount / 7 % 6)));
			sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
			sprite_shadow.setPosition(sprite.getPosition().x + 5, sprite.getPosition().y + 57);
			handPosition = handUp + sf::Vector2f(1.5f, -1.5f);
		}

		if (pointingRight) {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerRO_" + std::to_string(++movingCount / 7 % 6)));
			sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
			sprite_shadow.setPosition(sprite.getPosition().x + 4, sprite.getPosition().y + 59);
			handPosition = handRight + sf::Vector2f(4.5, -10);
		}
		else if (pointingUpRight) {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerUR_" + std::to_string(++movingCount / 7 % 6)));
			sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
			sprite_shadow.setPosition(sprite.getPosition().x + 4, sprite.getPosition().y + 55);
			handPosition = handUpRight + sf::Vector2f(1, -2.5);
		}
		else if (pointingLeft) {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerRO_" + std::to_string(++movingCount / 7 % 6)));
			sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
			handPosition = handLeft + sf::Vector2f(-3.5, -10);
			sprite_shadow.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y + 59);
		}
		else if (pointingUpLeft) {
			sprite.setTexture(TextureClass::get()->retrieveTexture("playerUR_" + std::to_string(++movingCount / 7 % 6)));
			sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
			sprite_shadow.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y + 55);
			handPosition = handLeft + sf::Vector2f(-0.5, -5);
		}
	}
	else if (dodging) {

		if (++dodgingCount / 5 == 9) {
			if (pointingRight || pointingLeft) {

				//for rolling into walls
				if (pointingRight) {
					movement.x += 100;
				}
				else {
					movement.x -= 100;
				}

				movement.y -= sum.y;
				view_movement.y -= movement.y;;
			}
			dodgingCount = -1;
			dodging = false;
			damageEnabled = true;
			sum.y = 0;
		}
		else {

			int dCount = dodgingCount / 5;
			int initial_speed = 250;

			float descent;
			if (dCount <= 2) { descent = initial_speed * dCount - (100.f / 2) * powf((float)dCount, 2.f); }
			else if (dCount <= 4) { descent = -1 * (initial_speed * dCount - (100.f / 2) * powf((float)dCount, 2.f)); }
			else { descent = 0; }

			if (pointingDownRight) {
				movement.y -= descent / 3;
				if (dCount == 0 || dCount == 1 || dCount == 2) {
					movement += sf::Vector2f(PlayerSpeed * 1.3f, PlayerSpeed * 1.3f);
				}
				else if (dCount == 3) {
					movement += sf::Vector2f(PlayerSpeed * 1.1f, PlayerSpeed * 1.1f);
					sprite_shadow.move(sf::Vector2f(0, -80.f) * deltaTime.asSeconds());
				}
				else if (dCount == 4) {
					movement += sf::Vector2f(PlayerSpeed, PlayerSpeed);
					sprite_shadow.move(sf::Vector2f(0, -100.f) * deltaTime.asSeconds());
				}
				else if (dCount == 5 || dCount == 6 || dCount == 7 || dCount == 8) {
					movement += sf::Vector2f(PlayerSpeed, PlayerSpeed);
					movement.y += -50;
				}

				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_RO_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
			}
			else if (pointingDownLeft) {
				movement.y -= descent / 3;
				if (dCount == 0 || dCount == 1 || dCount == 2) {
					movement += sf::Vector2f(PlayerSpeed * 1.3f * -1, PlayerSpeed * 1.3f);
				}
				else if (dCount == 3) {
					movement += sf::Vector2f(PlayerSpeed * 1.1f * -1, PlayerSpeed * 1.1f);
					sprite_shadow.move(sf::Vector2f(0, -80.f) * deltaTime.asSeconds());
				}
				else if (dCount == 4) {
					movement += sf::Vector2f(PlayerSpeed * -1, PlayerSpeed);
					sprite_shadow.move(sf::Vector2f(0, -100.f) * deltaTime.asSeconds());
				}
				else if (dCount == 5 || dCount == 6 || dCount == 7 || dCount == 8) {
					movement += sf::Vector2f(PlayerSpeed * -1, PlayerSpeed);
					movement.y += -50;
				}

				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_RO_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
			}
			else if (pointingDown) {
				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_DO_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
				if (dCount == 0 || dCount == 1) {
					movement.y += (PlayerSpeed * 2);
					sprite.scale(1.015f, 1.015f);
				}
				else if (dCount == 2 || dCount == 3) {
					movement.y += (PlayerSpeed * 1.15f);
					sprite.scale(1 / 1.015f, 1 / 1.015f);
				}
				else {
					movement.y += (PlayerSpeed * 1.15f);
				}
				sprite_shadow.move(sf::Vector2f(-5, -35) * deltaTime.asSeconds());
			}
			else if (pointingUp) {
				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_UO_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
				if (dCount == 0 || dCount == 1) {
					movement.y -= (PlayerSpeed * 2);
					sprite.scale(1.01f, 1.01f);
				}
				else if (dCount == 2 || dCount == 3) {
					movement.y -= (PlayerSpeed * 1.15f);
					sprite.scale(1 / 1.01f, 1 / 1.01f);
				}
				else {
					movement.y -= (PlayerSpeed * 1.15f);
				}
				sprite_shadow.move(sf::Vector2f(-5, -43) * deltaTime.asSeconds());
			}
			else if (pointingRight) {
				movement.y -= descent / 2.5f;
				if (dCount == 0 || dCount == 1 || dCount == 2) {
					movement.x += (PlayerSpeed * 2.f);
				}
				else if (dCount == 3) {
					movement.x += (PlayerSpeed * 1.5f);
				}
				else if (dCount == 4) {
					movement.x += (PlayerSpeed * 1.25f);
					movement.y += 150;
					sprite_shadow.move(sf::Vector2f(0, -150.f) * deltaTime.asSeconds());
				}
				else if (dCount == 5) {
					movement.x += (PlayerSpeed);
					movement.y += 150;
					sprite_shadow.move(sf::Vector2f(0, -100.f) * deltaTime.asSeconds());
				}
				else if (dCount == 6 || dCount == 7 || dCount == 8) {
					movement.x += (PlayerSpeed);
				}
				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_RO_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
				view_movement.y -= movement.y;
				sum.y += movement.y;
			}
			else if (pointingLeft) {
				movement.y -= descent / 3;
				if (dCount == 0 || dCount == 1 || dCount == 2) {
					movement.x -= (PlayerSpeed * 2.f);
				}
				else if (dCount == 3) {
					movement.x -= (PlayerSpeed * 1.5f);
				}
				else if (dCount == 4) {
					movement.x -= (PlayerSpeed * 1.25f);
					movement.y += 150;
					sprite_shadow.move(sf::Vector2f(0, -150.f) * deltaTime.asSeconds());
				}
				else if (dCount == 5) {
					movement.x -= (PlayerSpeed);
					movement.y += 150;
					sprite_shadow.move(sf::Vector2f(0, -100.f) * deltaTime.asSeconds());
				}
				else if (dCount == 6 || dCount == 7 || dCount == 8) {
					movement.x -= PlayerSpeed;
				}

				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_RO_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
				view_movement.y -= movement.y;
				sum.y += movement.y;
			}
			else if (pointingUpRight) {
				movement.y -= descent / 3;
				if (dCount == 0 || dCount == 1 || dCount == 2) {
					movement += sf::Vector2f(PlayerSpeed * 1.3f, PlayerSpeed * 1.3f * -1);
				}
				else if (dCount == 3) {
					movement += sf::Vector2f(PlayerSpeed * 1.1f, PlayerSpeed * 1.1f * -1);
					sprite_shadow.move(sf::Vector2f(0, -80.f) * deltaTime.asSeconds());
				}
				else if (dCount == 4) {
					movement += sf::Vector2f(PlayerSpeed, PlayerSpeed * -1);
					sprite_shadow.move(sf::Vector2f(0, -100.f) * deltaTime.asSeconds());
				}
				else if (dCount == 5 || dCount == 6 || dCount == 7 || dCount == 8) {
					movement += sf::Vector2f(PlayerSpeed, PlayerSpeed * -1);
					movement.y += -50;
				}

				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_UR_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
			}
			else if (pointingUpLeft) {
				movement.y -= descent / 3;
				if (dCount == 0 || dCount == 1 || dCount == 2) {
					movement += sf::Vector2f(PlayerSpeed * 1.3f * -1, PlayerSpeed * 1.3f * -1);
				}
				else if (dCount == 3) {
					movement += sf::Vector2f(PlayerSpeed * 1.1f * -1, PlayerSpeed * 1.1f * -1);
					sprite_shadow.move(sf::Vector2f(0, -80.f) * deltaTime.asSeconds());
				}
				else if (dCount == 4) {
					movement += sf::Vector2f(PlayerSpeed * -1, PlayerSpeed * -1);
					sprite_shadow.move(sf::Vector2f(0, -100.f) * deltaTime.asSeconds());
				}
				else if (dCount == 5 || dCount == 6 || dCount == 7 || dCount == 8) {
					movement += sf::Vector2f(PlayerSpeed * -1, PlayerSpeed * -1);
					movement.y += -50;
				}

				sprite.setTexture(TextureClass::get()->retrieveTexture("playerDodge_UR_" + std::to_string(dCount)));
				sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
			}

		}

	}

}

void Player::playerIdleUpdate() {

	movingCount = 0;
	if (pointingDown) {
		sprite.setTexture(TextureClass::get()->retrieveTexture("playerDO_"));
		sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
		sprite_shadow.setPosition(sprite.getPosition().x + 5, sprite.getPosition().y + 56);
		handPosition = handDown;
	}
	else if (pointingUp) {
		sprite.setTexture(TextureClass::get()->retrieveTexture("playerUO_"));
		sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
		sprite_shadow.setPosition(sprite.getPosition().x + 5, sprite.getPosition().y + 57);
		handPosition = handUp;
	}
	else if (pointingRight) {
		sprite.setTexture(TextureClass::get()->retrieveTexture("playerRO_"));
		sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
		sprite_shadow.setPosition(sprite.getPosition().x + 4, sprite.getPosition().y + 59);
		handPosition = handRight;
	}
	else if (pointingUpRight) {
		sprite.setTexture(TextureClass::get()->retrieveTexture("playerUR_"));
		sprite.setTextureRect(sf::IntRect(0, 0, (int)sprite.getTexture()->getSize().x, (int)sprite.getTexture()->getSize().y));
		sprite_shadow.setPosition(sprite.getPosition().x + 4, sprite.getPosition().y + 55);
		handPosition = handUpRight;
	}
	else if (pointingLeft) {
		sprite.setTexture(TextureClass::get()->retrieveTexture("playerRO_"));
		sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
		sprite_shadow.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y + 59);
		handPosition = handLeft;
	}
	else if (pointingUpLeft) {
		sprite.setTexture(TextureClass::get()->retrieveTexture("playerUR_"));
		sprite.setTextureRect(sf::IntRect((int)sprite.getTexture()->getSize().x, 0, (int)sprite.getTexture()->getSize().x * -1, (int)sprite.getTexture()->getSize().y));
		sprite_shadow.setPosition(sprite.getPosition().x + 2, sprite.getPosition().y + 55);
		handPosition = handUpLeft;
	}

}

void Player::playerRender(sf::RenderWindow& window) {
	window.draw(sprite_shadow);
	window.draw(pistol2.getsprite());
	for (int i = 0; i <= pistol2.getBulletCount(); i++) {
		if (pistol2.getBullets().at(i)->getIsShot()) {
			window.draw(pistol2.getBullets().at(i)->get_bullet_sprite());
		}
	}

	if (!dodging && !isDead) {
		window.draw(pistol.getsprite());
		for (int i = 0; i <= pistol.getBulletCount(); i++) {
			if (pistol.getBullets().at(i)->getIsShot()) {
				window.draw(pistol.getBullets().at(i)->get_bullet_sprite());
			}
		}
	}

	if (pointingUp && !dodging && !isDead) { window.draw(sprite_hand); }
	window.draw(sprite);
	if (!pointingUp && !dodging && !isDead) { window.draw(sprite_hand); }

}

bool Player::isPointingUp() const {
	return pointingUp;
}

void Player::takeDamage(int damage) {
	health -= damage;
}

sf::Sprite& Player::getSprite() {
	return sprite;
}