// json_parser.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "JSONParser.h"


int main()
{
	JSONParser* jsonParser = new JSONParser();
	jsonParser->parse("example_json.json");
	jsonParser->printAllJSON();
	system("pause");
    return 0;
}

