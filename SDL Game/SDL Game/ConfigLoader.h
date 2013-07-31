#pragma once
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
class ConfigLoader
{
public:
	static void OpenConfig(const char* fileName);
	static int ReadInt(std::string key);
	static std::string ReadString(std::string key);
private:
	static std::map<std::string, std::string> KeyValuesMap;
};

