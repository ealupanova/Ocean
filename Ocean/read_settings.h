#pragma once
#include <string>
#include <fstream>

class ReadSettings 
{
public:
	static void ReadSettingsFile(std::string fileName = "configuration.ini");
private:
	static bool ReadOceanParam(std::ifstream& fin);
	static bool ReadPlanktonParam(std::ifstream& fin);
	static bool ReadFishParam(std::ifstream& fin);
	static bool ReadSharkParam(std::ifstream& fin);

};