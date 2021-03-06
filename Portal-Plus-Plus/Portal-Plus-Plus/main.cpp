#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include "player.h"
#include "world.h"
#include "enemy.h"
#include "key_handler.h"
#include "mouse_handler.h"
#include "level_view.h"


int main()
{

	// redirect cout to point to cout.txt for debugging purposes
	std::ofstream file;
	file.open("cout.txt");
	std::streambuf* sbuf = std::cout.rdbuf();
	std::cout.rdbuf(file.rdbuf());

	// initialize the static vector of levels
	World::initLevels();

	// load the font for rendering game over screens
	sf::Font font;
	font.loadFromFile(ASSET_DIR + "/font.ttf");

	// configure rendering window
	RenderWindow * window = new RenderWindow(VideoMode(W * UNIT, H * UNIT), "Portal++");
	window->setMouseCursorVisible(false);
	window->setFramerateLimit(60);

	// load textures from files for displaying graphics
	Texture * tileSet = new Texture();
	tileSet->loadFromFile(ASSET_DIR + "/SpriteSheet1.png");

	Texture * background_texture = new Texture();
	background_texture->loadFromFile(ASSET_DIR + "/Background.png");
	sf::Sprite background(*background_texture);

	Sprite tile(*tileSet);

	Sprite * life = new Sprite(*tileSet);
	life->setTextureRect(IntRect(3 + UNIT * 2, 13 + UNIT * 7, UNIT, UNIT));

	sf::Sprite * crosshair = new sf::Sprite(*tileSet);
	crosshair->setTextureRect(IntRect(2 * UNIT, 2 * UNIT, UNIT, UNIT));

	// seed random generator used for determining direction of spawned enemies
	srand(time(NULL));

	// dynamically allocate model, view, and controller
	GameModel * model = new GameModel();
	KeyHandler * key_handler = new KeyHandler(model);
	MouseHandler * mouse_handler = new MouseHandler(model);
	LevelView * view = new LevelView(model, life);


	// start playing the background music
	sf::Music music;
	music.openFromFile(ASSET_DIR + "/song.ogg");
	music.play();



	bool game_over = false;

	// run each of the levels while the player is still alive
	for (int level = 0; level < World::getNumLevels(); ++level) {
		
		// create new components for this level
		World::setLevel(level);
		Player player;
		std::vector<Enemy*> enemies;
		FloatRect door;

		// set the locations of the components based on their spot in the level map
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++)
			{
				// found enemy
				if (World::TileMap[i][j] == 'X') {
					Enemy *enemy = new Enemy();
					enemy->set(*tileSet, j * UNIT, i * UNIT);
					enemies.push_back(enemy);
					if (rand() % 2 == 0) {
						enemy->dx *= -1;
					}
				}
				// found player
				else if (World::TileMap[i][j] == 'P') {
					player = Player(*tileSet, j * UNIT, i * UNIT);
				}
				// found exit door
				else if (World::TileMap[i][j] == 'E') {
					// set the rectangle of the door to a space just above the floor
					// where the door contacts the ground
					door = FloatRect((j + 0.45) * UNIT, (i + 2) * UNIT - 10,
						UNIT / 10.0, UNIT);
					std::cout << "FOUND DOOR" << std::endl;
					std::cout << door.top << std::endl;
					std::cout << door.left << std::endl;
				}
			}
		}

		// clock used for tracking time intervals between main loop cycles
		Clock clock;
		

		*model = GameModel(tileSet, &player, enemies, door);


		while (!window->isOpen() && !game_over) {
			// wait for the window to open to prevent the game loop from
			// being skipped
		}

		// loop through the game until it the level is over or the window closes
		while (window->isOpen())
		{
			// set the position of the crosshair based on the mosue position
			sf::Vector2i mouse_coords = sf::Mouse::getPosition(*window);
			crosshair->setPosition(mouse_coords.x, mouse_coords.y);

			// get the clock time that has elapsed since the last clock tick to account for
			// any missed frames
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time = time / 500;

			// don't skip too many frames at once
			if (time > 20) {
				time = 20;
			}

			// poll events and delegate to the mouse handler if there was a click
			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window->close();
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					mouse_handler->handleMouse(event);
				}
			}

			// handles any keys that are currently pressed down
			key_handler->handleKey();

			// updates all game objects in the model
			model->update(time);

			// clear the window to a black background
			window->clear(Color(0, 0, 0));
			window->draw(background);

			// draw the level
			for (int i = 0; i < H; i++) {
				for (int j = 0; j < W; j++)
				{
					if (World::TileMap[i][j] == 'F')  tile.setTextureRect(IntRect(2 * UNIT + 3, 3 * UNIT, UNIT, UNIT));
					if (World::TileMap[i][j] == 'W')  tile.setTextureRect(IntRect(3 * UNIT + 3, 0, UNIT, UNIT));
					if (World::TileMap[i][j] == ' ' || World::TileMap[i][j] == '0' || World::TileMap[i][j] == 'X' || World::TileMap[i][j] == 'P') continue;
					if (World::TileMap[i][j] == 'E')  tile.setTextureRect(IntRect(2 * UNIT + 3, 5.25 * UNIT, UNIT, 2 * UNIT));
					tile.setPosition(j*UNIT - offsetX, i*UNIT - offsetY);
					window->draw(tile);
				}
			}

			// has the player lost the game?
			if (player.lives_remaining <= 0) {
				game_over = true;
				player.sprite.setColor(Color::Red);
			}


			// render the game objects on top of the level
			view->render(window);
			// draw the crosshair at the current mouse location
			window->draw(*crosshair);
			// display the window
			window->display();

			// has the player beaten the current level?
			if (model->reachedDoor()) {
				std::cout << World::getCurrentLevel() << std::endl;
				std::cout << World::getNumLevels() << std::endl;
				World::setCurrentLevel(World::getCurrentLevel() + 1);
				if (World::isGameWon()) {
					game_over = true;
					std::cout << "WON THE GAME" << std::endl;
				}
				World::setLevel(World::getCurrentLevel() + 1);
				break;
			}

			if (game_over) {
				break;
			}

		}
		// display the final message screen
		if (game_over) {
			std::cout << World::getCurrentLevel() << std::endl;
			std::cout << World::getNumLevels() << std::endl;
			sf::Text message;
			message.setFont(font);
			message.setCharacterSize(72);
			if (World::isGameWon()) {
				message.setString("YOU WIN!");
				message.setColor(sf::Color::Green);
			}
			else {
				message.setString("GAME OVER");
				message.setColor(sf::Color::Red);
			}
			message.setPosition(UNIT * W / 2 - 200, UNIT * H / 2 - 80);
			
			while (window->isOpen()) {
				Event event;
				while (window->pollEvent(event))
				{
					if (event.type == Event::Closed) {
						window->close();
					}
				}
				sf::Vector2i mouse_coords = sf::Mouse::getPosition(*window);
				crosshair->setPosition(mouse_coords.x, mouse_coords.y);
				window->clear();
				window->draw(*crosshair);
				window->draw(message);
				window->display();
			}
			

		}
		if (!window->isOpen()) {
			return 0;
		}


	}
	// deallocate all objects from the heap
	delete model;
	delete key_handler;
	delete mouse_handler;
	delete view;
	delete tileSet;
	delete life;
	delete crosshair;
	return 0;
}



