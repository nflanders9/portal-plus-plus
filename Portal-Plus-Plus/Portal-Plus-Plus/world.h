#ifndef WORLD
#define WORLD

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <iostream>

using namespace sf;

const std::string ASSET_DIR = "../assets";

const int UNIT = 32;

float static offsetX = 0;
float static offsetY = 0;

const int H = 18;
const int W = 40;


// represents a world/level
class World {
public:
	static String TileMap[H];
	World() = default;
	
	// set the current level
	static void setLevel(int level);

	// represents the current level number
	static int current_level;

	// must be called on to create level array vector
	static void initLevels();

	// update the model based on the current level map
	//static void updateModel(GameModel * model);

private:
	static std::vector<String*> m_levels;
};

#endif // WORLD

