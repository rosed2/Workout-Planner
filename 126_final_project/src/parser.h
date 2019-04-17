

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