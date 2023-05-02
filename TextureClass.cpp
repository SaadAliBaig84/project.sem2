#include "TextureClass.h"

TextureClass* TextureClass::instance = nullptr;

TextureClass::TextureClass() {
	instance = this;

	//Background
	TextureClass::get()->addTexture("StartingAreaFloor", "Texture/Background/SA_floor.png");
	TextureClass::get()->addTexture("StartingAreaWall", "Texture/Background/SA_wall.png");
	TextureClass::get()->addTexture("SA_BridgeFloor", "Texture/Background/SA_bridge_floor.png");
	TextureClass::get()->addTexture("SA_BridgeWall", "Texture/Background/SA_bridge_wall.png");

	TextureClass::get()->addTexture("InitialAreaFloor", "Texture/Background/IA_floor.png");
	TextureClass::get()->addTexture("InitialAreaWall", "Texture/Background/IA_wall.png");
	TextureClass::get()->addTexture("IA_BridgeFloor", "Texture/Background/IA_bridge_floor.png");
	TextureClass::get()->addTexture("IA_BridgeWall", "Texture/Background/IA_bridge_wall.png");


	//Player
	TextureClass::get()->addTexture("playerDO_", "Texture/Player/DO_.png");
	TextureClass::get()->addTexture("playerRO_", "Texture/Player/RO_.png");
	TextureClass::get()->addTexture("playerUO_", "Texture/Player/UO_.png");
	TextureClass::get()->addTexture("playerUR_", "Texture/Player/UR_.png");

	for (int i = 0; i <= 5; i++) {
		std::string temp = std::to_string(i);
		TextureClass::get()->addTexture("playerDO_" + temp, "Texture/Player/DO_" + temp + ".png");
		TextureClass::get()->addTexture("playerRO_" + temp, "Texture/Player/RO_" + temp + ".png");
		TextureClass::get()->addTexture("playerUO_" + temp, "Texture/Player/UO_" + temp + ".png");
		TextureClass::get()->addTexture("playerUR_" + temp, "Texture/Player/UR_" + temp + ".png");
	}

	for (int i = 0; i <= 8; i++) {
		std::string temp = std::to_string(i);
		TextureClass::get()->addTexture("playerDodge_DO_" + temp, "Texture/Player/Dodge_DO_" + temp + ".png");
		TextureClass::get()->addTexture("playerDodge_RO_" + temp, "Texture/Player/Dodge_RO_" + temp + ".png");
		TextureClass::get()->addTexture("playerDodge_UO_" + temp, "Texture/Player/Dodge_UO_" + temp + ".png");
		TextureClass::get()->addTexture("playerDodge_UR_" + temp, "Texture/Player/Dodge_UR_" + temp + ".png");

		TextureClass::get()->addTexture("playerDeath_DE_" + temp, "Texture/Player/DE_" + temp + ".png");
	}

	TextureClass::get()->addTexture("playerHand", "Texture/Player/Hand.png");
	TextureClass::get()->addTexture("playerShadow", "Texture/Player/shadow.png");


	//Gun
	TextureClass::get()->addTexture("Enemy_Pistol", "Texture/Gun/Enemy_Pistol.png");
	TextureClass::get()->addTexture("Player_Pistol", "Texture/Gun/Player_Pistol.png");
	TextureClass::get()->addTexture("SMG", "Texture/Gun/smg1.png");
	TextureClass::get()->addTexture("Reload", "Texture/Gun/reload.png");
	TextureClass::get()->addTexture("Reload_BG", "Texture/Gun/reload_bg.png");

	//Bullet
	TextureClass::get()->addTexture("Enemy_Pistol_Bullet", "Texture/Bullet/bullet4.png");
	TextureClass::get()->addTexture("Player_Pistol_Bullet", "Texture/Bullet/bullet3.png");
	TextureClass::get()->addTexture("SMG_Bullet", "Texture/Bullet/bullet2.png");


	//HUD
	TextureClass::get()->addTexture("playerHealth", "Texture/HUD/player_health.png");

}

TextureClass* TextureClass::get() {
	return instance;
}

void TextureClass::addTexture(const std::string label, const std::string& filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename)) {
		throw std::runtime_error("TextureClass::addTexture() - Failed to load " + filename);
	}
	TextureMap.insert(std::make_pair(label, std::move(texture)));
}

sf::Texture& TextureClass::retrieveTexture(const std::string label) {
	auto  result = TextureMap.find(label);
	return *(result->second);
}