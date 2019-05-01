//Created 4-17-19 by Rose Dinh

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

//Method to create an array of Exercise objects from a json file
vector<Exercise> Parser::ReadExercises() {
	std::string file = "exercises.json";
	vector<Exercise> to_return;

	// Now parse the JSON
	bool parsingSuccessful = result.open(file);
	if (!parsingSuccessful) {
		cout << "Parsing unsuccessful" << std::endl;
		return to_return;
	}

	//Lines 33-38 from https://stackoverflow.com/questions/46203948/reading-array-of-the-json-in-jsoncpp

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

	return to_return;
}