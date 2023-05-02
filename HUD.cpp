#include "HUD.h"

HUD::HUD() {

	for (int i = 0; i < 4; i++) {
		health_sprite_vector.push_back(sf::Sprite(TextureClass::get()->retrieveTexture("playerHealth")));
		health_sprite_vector.at(i).setScale(1.7f, 1.7f);
	}

	numOfHearts = 4;
	health_sprite_size = sf::Vector2i(TextureClass::get()->retrieveTexture("playerHealth").getSize());
	proxy = false;
}

void HUD::hudUpdate(float health, sf::View& view, bool reloading) {

	sf::Vector2f view_center = view.getCenter();
	sf::Vector2f view_size = view.getSize();

	sf::Vector2f delta = view_center - view_size / 2.2f;

	for (float i = 0; i < ceil(numOfHearts); i++) {
		health_sprite_vector.at(int(i)).setPosition(sf::Vector2f(delta.x + i * 2.1f * health_sprite_size.x, delta.y));
	}

	numOfHearts = health;

	reload_bg.setTexture(TextureClass::get()->retrieveTexture("Reload_BG"));
	reload_bg.setPosition(view_center + sf::Vector2f(view_size.x / 2.9f, view_size.y / 4.f));
	reload_bg.setScale(0.16f, 0.25f);

	reload.setTexture(TextureClass::get()->retrieveTexture("Reload"));
	reload.setOrigin(sf::Vector2f(reload.getTexture()->getSize()) / 2.f);
	reload.setPosition(reload_bg.getPosition() + sf::Vector2f(reload_bg.getTexture()->getSize().x * reload_bg.getScale().x, reload_bg.getTexture()->getSize().y * reload_bg.getScale().y) / 2.f);
	reload.setScale(0.7f, 0.7f);

	if (reloading) {
		proxy = true;
	}

	if (reloading)
	{
		reload.rotate(3.f);
	}
	else if (proxy) {
		reload.setRotation(0.f);
		proxy = false;
	}


}

void HUD::hudRender(sf::RenderWindow& window) {

	for (int i = 0; i < numOfHearts; i++) {

		if (numOfHearts - i == 0.5) {
			health_sprite_vector.at(i).setTextureRect(sf::IntRect(0, 0, health_sprite_size.x / 2, health_sprite_size.y));
		}

		window.draw(health_sprite_vector.at(i));
		health_sprite_vector.at(i).setTextureRect(sf::IntRect(sf::Vector2i(0, 0), health_sprite_size));
	}

	window.draw(reload_bg);
	window.draw(reload);
}

//sf::Sprite& HUD::getHealthSprite() {
//	return health_sprite;
//}