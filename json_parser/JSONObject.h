#pragma once
#include <vector>
#include <utility>

class JSONObject
{
public:
	JSONObject();
	~JSONObject();

	void setParent(JSONObject *jsonObject);
	JSONObject* getParent();

	std::vector<std::pair<std::string, JSONObject*>> childs;
	std::vector<std::pair<std::string, std::string>> notes;

private:
	JSONObject* parent;
};

