#pragma once

#include "unit.h"
#include <list>
#include "SFML/Graphics.hpp"


class Ocean
{
public:
	Ocean();
	~Ocean() {}
	void ColonizeOcean();
	void Live(sf::RenderWindow &window, sf::Sprite& sprite);
	static void SetSize(int rows, int cols) { ROWS = rows; COLS = cols; }
	static void SetStartCounts(int plankton, int fish, int shark, bool center) { startPlankton = plankton; startFish = fish; startShark = shark; isCenter = center; }
	static int GetCols() { return COLS; }
	static int GetRows() { return ROWS; }
private:
	std::list<Unit*> units;
	std::vector<std::vector<Unit*>> ocean;
	static int ROWS, COLS;
	static int startPlankton, startFish, startShark;
	static bool isCenter;
	void PrintOcean(sf::RenderWindow& window, sf::Sprite& sprite, int step);
	void OceanLive(std::list<Unit*>& new_unit);
	int PrintStateOcean(const std::list<Unit*>& new_unit, int step);
};

