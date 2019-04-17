
#include "parser.h"
#include <string>
#include <vector>
#include <algorithm>
#include <ostream>

using std::cout;
using std::string;
using std::vector;

Parser::Parser() {

}

Parser::~Parser() {

}

vector<Exercise> Parser::ReadExercises() {
	std::string file = "exercises.json";
	vector<Exercise> to_return;

	// Now parse the JSON
	bool parsingSuccessful = result.open(file);
	if (!parsingSuccessful) {
		cout << "Parsing unsuccessful" << std::endl;
		return to_return;
	}

	//Lines 26-31 from https://stackoverflow.com/questions/46203948/reading-array-of-the-json-in-jsoncpp

	Json::Reader reader;
	Json::Value root;

	reader.parse(result.getRawString(), root, false);

	auto entriesArray = root["exercises"];

	for (unsigned int i = 0; i < entriesArray.size(); i++) {
		string name = entriesArray[i]["name"].asString();
		string muscle = entriesArray[i]["muscle"].asString();
		string equipment = entriesArray[i]["equipment"].asString();
		Exercise to_add = Exercise(name, muscle, equipment);
		to_return.push_back(to_add);
	}
	
	cout << to_return[0].GetName() << " " << to_return[0].GetMuscle() << std::endl;
	cout << to_return[0].GetEquipment() << std::endl;

	return to_return;
}