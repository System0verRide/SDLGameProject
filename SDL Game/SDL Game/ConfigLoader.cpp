#include "ConfigLoader.h"

std::map<std::string, std::string> ConfigLoader::KeyValuesMap;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void ConfigLoader::OpenConfig(const char* fileName)
{
	std::fstream filestream(fileName, std::ios::in);
	KeyValuesMap = std::map<std::string, std::string>();
	std::vector<std::string> fileLines;
	while(!filestream.eof())
	{
		std::string tempString;
		std::getline(filestream, tempString);
		fileLines.push_back(tempString);
	}

	//split the string value and token
	for(int i = 0; i < fileLines.size(); i++)
	{
		std::vector<std::string> temp;
		temp = split(fileLines.at(i), ' ');
		auto it = KeyValuesMap.begin();
		KeyValuesMap.insert(it, std::pair<std::string, std::string>(temp.at(0), temp.at(1)));
	}
}

int ConfigLoader::ReadInt(std::string key)
{
	std::string temp = KeyValuesMap.find(key)->second;
	return atoi(temp.c_str());
}

std::string ConfigLoader::ReadString(std::string key)
{
	std::string ret = KeyValuesMap.find(key)->second;
	return ret;
}