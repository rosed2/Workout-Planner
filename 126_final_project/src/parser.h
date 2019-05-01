//Represents a parser object, reads exercise data from a json file
//Created 4-17-19 by Rose Dinh

#pragma once

#include "ofxJSON.h"
#include "exercise.h"
#include <string>
#include <vector>

class Parser
{
public:
	Parser();
	~Parser();
	std::vector<Exercise> ReadExercises();
	ofxJSONElement result;
};