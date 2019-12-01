#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "JSONObject.h"
#include <vector>

enum States {

};

class JSONParser
{
public:
	JSONParser();
	~JSONParser();
	void parsing(std::string filepath);
	void printAllJSON();
	

private:
	JSONObject *currentJSONObject;
	std::vector<JSONObject*> jsons;

	void printJSON(JSONObject* json);

	void parsingLine(std::string line);
	
	std::string preprocessLine(std::string line);
	std::string removeComma(std::string line);
	std::string removeQuotes(std::string line);
	std::string removeSpaces(std::string line);
	std::string removeTabs(std::string line);

	std::vector<std::string> split(std::string line, std::string delimiter);

	bool isOpenFigureBracket(std::string line);
	bool isClosedFigureBracket(std::string line);
	bool isSimpleNote(std::string line);
	bool isBracket(std::string line);
	bool isJSONObject(std::string line);

};

