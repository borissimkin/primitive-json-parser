#include "stdafx.h"
#include "JSONParser.h"


JSONParser::JSONParser()
{
	this->currentJSONObject = nullptr;
}


JSONParser::~JSONParser()
{
}


void JSONParser::parsing(std::string filepath)
{
	std::ifstream file(filepath);
	if (!file)
	{
		std::cout << "Файл не открыт\n\n";
	}
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		this->parsingLine(line);
	}
}

void JSONParser::printAllJSON()
{
	for (int i = 0; i < this->jsons.size(); i++)
	{
		std::cout << "{\n";
		this->printJSON(jsons[i]);
		std::cout << "}\n";
	}

}


void JSONParser::printJSON(JSONObject * json)
{
	if (json == nullptr)
	{
		return;
	}
	for (int i = 0; i < json->notes.size(); i++)
	{
		std::cout << json->notes[i].first << ":" << json->notes[i].second << "\n";
	}
	for (int i = 0; i < json->childs.size(); i++)
	{
		std::cout << json->childs[i].first << ": {\n";
		this->printJSON(json->childs[i].second);
		std::cout << "}\n";
	}
}

void JSONParser::parsingLine(std::string line)
{
	line = this->preprocessLine(line);
	if (this->isOpenFigureBracket(line))
	{
		JSONObject* jsonObject = new JSONObject();
		jsonObject->setParent(this->currentJSONObject);
		this->currentJSONObject = jsonObject;
		this->jsons.push_back(jsonObject);
	}
	else if (this->isClosedFigureBracket(line))
	{
		this->currentJSONObject = this->currentJSONObject->getParent();
	}
	else if (this->isSimpleNote(line))
	{
		std::pair<std::string, std::string> note;
		std::vector<std::string> splitResult = this->split(line, ":");
		note.first = splitResult[0];
		note.second = splitResult[1];
		this->currentJSONObject->notes.push_back(note);
	}
	else if (this->isJSONObject(line))
	{
		std::pair<std::string, JSONObject*> noteJSON;
		std::vector<std::string> splitResult = this->split(line, ":");
		
		JSONObject *json = new JSONObject();
		
		json->setParent(this->currentJSONObject);
		noteJSON.first = splitResult[0];
		noteJSON.second = json;
		this->currentJSONObject->childs.push_back(noteJSON);
		this->currentJSONObject = json;
	}
}

std::string JSONParser::preprocessLine(std::string line)
{
	line = this->removeComma(line);
	line = this->removeQuotes(line);
	line = this->removeSpaces(line);
	line = this->removeTabs(line);
	return line;
}

std::string JSONParser::removeComma(std::string line)
{
	std::string result;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ',')
		{
			result.push_back(line[i]);
		}
	}
	return result;
}

std::string JSONParser::removeQuotes(std::string line)
{
	std::string result;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != '\"')
		{
			result.push_back(line[i]);
		}
	}
	return result;
}

std::string JSONParser::removeSpaces(std::string line)
{
	std::string result = "";
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')
		{
			result.push_back(line[i]);
		}
	}
	return result;
}

std::string JSONParser::removeTabs(std::string line)
{
	std::string result;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != '\t')
		{
			result.push_back(line[i]);
		}
	}
	return result;
}

std::vector<std::string> JSONParser::split(std::string line, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos) {
		token = line.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(line.substr(pos_start));
	return res;
}

bool JSONParser::isOpenFigureBracket(std::string line)
{
	if (line == "{")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool JSONParser::isClosedFigureBracket(std::string line)
{
	if (line == "}")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool JSONParser::isSimpleNote(std::string line)
{
	std::vector<std::string> resultSplit = this->split(line, ":");
	if (resultSplit.size() == 2)
	{
		if (!this->isBracket(resultSplit[0]) && !this->isBracket(resultSplit[1]))
		{
			return true;
		}
	}
	return false;
}

bool JSONParser::isBracket(std::string line)
{
	if (this->isOpenFigureBracket(line) || this->isClosedFigureBracket(line))
	{
		return true;
	}
	return false;
}

bool JSONParser::isJSONObject(std::string line)
{
	std::vector<std::string> resultSplit = this->split(line, ":");
	if (resultSplit.size() == 2)
	{
		if (!this->isBracket(resultSplit[0]) && this->isOpenFigureBracket(resultSplit[1]))
		{
			return true;
		}
	}
	return false;
}
