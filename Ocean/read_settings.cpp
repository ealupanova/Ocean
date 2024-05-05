
#include "read_settings.h"
#include "ocean.h"
#include "plankton.h"
#include "fish.h"
#include "shark.h"
#include <iostream>

void ReadSettings::ReadSettingsFile(std::string fileName)
{
	std::ifstream fin(fileName);
	if (!fin)
	{
		std::cerr << "Error opening configuration file. Default values will be used";
		return;
	}
	if (!ReadOceanParam(fin))
		return;
	if (!ReadPlanktonParam(fin))
		return;
	if (!ReadFishParam(fin))
		return;
	if (!ReadSharkParam(fin))
		return;
	fin.close();
}

bool ReadSettings::ReadOceanParam(std::ifstream& fin)
{
	int r, c;
	std::string pos;
	fin >> pos >> r;
	if (pos != "ROWS")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	fin >> pos >> c;
	if (pos != "COLS")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Ocean::SetSize(r, c);
	int p, f, s;
	std::string ct;
	bool cnt;
	fin >> pos >> p;
	if (pos != "PLANKTON")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	fin >> pos >> f;
	if (pos != "FISH")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	fin >> pos >> s;
	if (pos != "SHARK")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	fin >> pos >> ct;
	if (pos != "IS_CENTER")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	if (ct == "TRUE")
		cnt = true;
	else
		cnt = false;
	Ocean::SetStartCounts(p, f, s, cnt);
	return true;
}

bool ReadSettings::ReadPlanktonParam(std::ifstream& fin)
{
	int p;
	std::string pos;
	fin >> pos >> p;
	if (pos != "P_MAX_AGE")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Plankton::SetMaxAge(p);
	fin >> pos >> p;
	if (pos != "P_MAX_STEP")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Plankton::SetMaxStep(p);
	fin >> pos >> p;
	if (pos != "P_REPROD_TIME")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Plankton::SetReproductionTime(p);
	fin >> pos >> p;
	if (pos != "P_REPROD_FREQ")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Plankton::SetReproductionFreq(p);
	fin >> pos >> p;
	if (pos != "P_COUNT_NEIGH")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Plankton::SetCountNeighbours(p);
	return true;
}

bool ReadSettings::ReadFishParam(std::ifstream& fin)
{
	int p;
	std::string pos;
	fin >> pos >> p;
	if (pos != "F_MAX_AGE")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetMaxAge(p);
	fin >> pos >> p;
	if (pos != "F_MAX_STEP")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetMaxStep(p);
	fin >> pos >> p;
	if (pos != "F_MAX_VIEW")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetMaxView(p);
	fin >> pos >> p;
	if (pos != "F_REPROD_TIME")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetReproductionTime(p);
	fin >> pos >> p;
	if (pos != "F_REPROD_FREQ")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetReproductionFreq(p);
	fin >> pos >> p;
	if (pos != "F_HUN_FREQ")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetHungryFreq(p);
	fin >> pos >> p;
	if (pos != "F_HUN_MAX")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetHungryMax(p);
	fin >> pos >> p;
	if (pos != "F_COUNT_NEIGH")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Fish::SetCountNeighbours(p);
	return true;
}

bool ReadSettings::ReadSharkParam(std::ifstream& fin)
{
	int p;
	std::string pos;
	fin >> pos >> p;
	if (pos != "S_MAX_AGE")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetMaxAge(p);
	fin >> pos >> p;
	if (pos != "S_MAX_STEP")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetMaxStep(p);
	fin >> pos >> p;
	if (pos != "S_MAX_VIEW")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetMaxView(p);
	fin >> pos >> p;
	if (pos != "S_REPROD_TIME")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetReproductionTime(p);
	fin >> pos >> p;
	if (pos != "S_REPROD_FREQ")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetReproductionFreq(p);
	fin >> pos >> p;
	if (pos != "S_HUN_FREQ")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetHungryFreq(p);
	fin >> pos >> p;
	if (pos != "S_HUN_MAX")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetHungryMax(p);
	fin >> pos >> p;
	if (pos != "S_COUNT_NEIGH")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetCountNeighbours(p);
	fin >> pos >> p;
	if (pos != "S_HUN_REPR")
	{
		std::cerr << "Configuration file is corrupted. Default values will be used";
		fin.close();
		return false;
	}
	Shark::SetHungryReproduction(p);
	return true;
}
