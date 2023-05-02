#include "Game.h"

Game::Game() {

	window.setFramerateLimit(60);
	window.create(sf::VideoMode(1920, 1080), "My window");
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	//remove this chunk
	TextureClass::get()->addTexture("Enemy", "Texture/Player/RO_.png");
	enemy.setTexture(TextureClass::get()->retrieveTexture("Enemy"));
	enemy.setPosition(150, 350);

	player.getSprite().setPosition(sf::Vector2f(500, 300));
	view.setCenter(player.getSprite().getPosition());
	view.setSize(sf::Vector2f(window.getSize()));
	view.zoom(0.7f);


	sf::Vector2f tileSize = sf::Vector2f(16, 16);

	startingArea.loadFloor(&TextureClass::get()->retrieveTexture("StartingAreaFloor"), tileSize, 16, 9);
	startingArea.move(sf::Vector2f(tileSize.x * startingArea.getScale().x, tileSize.y * startingArea.getScale().y));
	allAreas.push_back(&startingArea);
	sf::Vector2i startingAreaExceptions[] = { sf::Vector2i(18, 4), sf::Vector2i(18, 5), sf::Vector2i(18, 6), sf::Vector2i(18, 7), sf::Vector2i(18,8) };
	startingAreaWall.loadWall(&TextureClass::get()->retrieveTexture("StartingAreaWall"), tileSize, 18, 11, startingAreaExceptions, 5);

	SA_bridge.loadFloor(&TextureClass::get()->retrieveTexture("SA_BridgeFloor"), tileSize, 10, 3);
	SA_bridge.move(sf::Vector2f(tileSize.x * 17 * startingArea.getScale().x, tileSize.y * 4 * startingArea.getScale().y));
	allAreas.push_back(&SA_bridge);
	sf::Vector2i SA_bridgeExceptions[] = { sf::Vector2i(1, 1), sf::Vector2i(1, 2), sf::Vector2i(1, 3), sf::Vector2i(1, 4), sf::Vector2i(1, 5), sf::Vector2i(12, 1), sf::Vector2i(12, 2), sf::Vector2i(12, 3), sf::Vector2i(12, 4), sf::Vector2i(12, 5) };
	SA_bridgeWall.loadWall(&TextureClass::get()->retrieveTexture("SA_BridgeWall"), tileSize, 12, 5, SA_bridgeExceptions, 10);
	SA_bridgeWall.setPosition(SA_bridge.getPosition() + sf::Vector2f(-48, -48));

	initialArea.loadFloor(&TextureClass::get()->retrieveTexture("InitialAreaFloor"), tileSize, 20, 20);
	initialArea.move(sf::Vector2f(tileSize.x * 27 * startingArea.getScale().x, tileSize.y * -2 * startingArea.getScale().y));
	allAreas.push_back(&initialArea);
	sf::Vector2i initialAreaExceptions[] = { sf::Vector2i(1,7), sf::Vector2i(1,8), sf::Vector2i(1,9), sf::Vector2i(1,10), sf::Vector2i(1,11), sf::Vector2i(10, 22), sf::Vector2i(11, 22), sf::Vector2i(12, 22), sf::Vector2i(13, 22), sf::Vector2i(14, 22) };
	initialAreaWall.loadWall(&TextureClass::get()->retrieveTexture("InitialAreaWall"), tileSize, 22, 22, initialAreaExceptions, 10);
	initialAreaWall.move(initialArea.getPosition() + sf::Vector2f(-48, -48));

	IA_bridge.loadFloor(&TextureClass::get()->retrieveTexture("IA_BridgeFloor"), tileSize, 3, 10);
	IA_bridge.setPosition(initialArea.getPosition() + sf::Vector2f(tileSize.x * 9 * startingArea.getScale().x, tileSize.y * 20 * startingArea.getScale().y));
	allAreas.push_back(&IA_bridge);
	sf::Vector2i IA_bridgeExceptions[] = { sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(3, 1), sf::Vector2i(4, 1), sf::Vector2i(5, 1) };
	IA_bridgeWall.loadWall(&TextureClass::get()->retrieveTexture("IA_BridgeWall"), tileSize, 5, 12, IA_bridgeExceptions, 5);
	IA_bridgeWall.setPosition(IA_bridge.getPosition() + sf::Vector2f(-48, -48));

	

}

void Game::run() {
	sf::Clock clock;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents() {

	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				std::cout << "End of Program." << std::endl;
				window.close();
			}
			player.playerKeyboardInput(event.key.code, true);
		}

		if (event.type == sf::Event::KeyReleased) {
			player.playerKeyboardInput(event.key.code, false);
		}

		if (event.type == sf::Event::MouseMoved) {
			player.playerMouseInput(window);
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			player.playerClickInput(event.mouseButton.button, true);
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			player.playerClickInput(event.mouseButton.button, false);
		}

		if (event.type == sf::Event::MouseWheelScrolled) {
			player.playerScrollInput(event.mouseWheelScroll.delta);
		}

	}
}

void Game::update(sf::Time deltaTime) {
	status = player.playerUpdate(deltaTime, window, view, enemy, allAreas);
	hud.hudUpdate(player.getHealth(), view, status.at(1));

}

void Game::render() {
	window.clear();

	window.setView(view);

	window.draw(SA_bridgeWall);
	window.draw(SA_bridge);
	window.draw(startingAreaWall);
	window.draw(startingArea);

	window.draw(IA_bridgeWall);
	window.draw(IA_bridge);
	window.draw(initialAreaWall);
	window.draw(initialArea);


	window.draw(enemy);
	player.playerRender(window);


	
	hud.hudRender(window);
	window.display();
}