#include "ocean.h"
#include "read_settings.h"
#include "SFML/Graphics.hpp"

int SIZE_RECT = 16;

int main()
{
	ReadSettings::ReadSettingsFile();
	sf::RenderWindow window;
	window.create(sf::VideoMode(Ocean::GetCols()*16, Ocean::GetRows()*16), "Ocean");
	sf::Image map_image;
	map_image.loadFromFile("map.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite sprite;
	sprite.setTexture(map);
	Ocean ocean;
	ocean.ColonizeOcean();
	ocean.Live(window, sprite);
	return 0;
}