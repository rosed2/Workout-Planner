

#include "workout_plan.h"
#include <string>
#include <vector>
#include <algorithm>


using std::string;
using std::vector;

WorkoutPlan::WorkoutPlan(string name, vector<Exercise>* exercises) {
	name_ = name;
	exercises_ = exercises;
}

WorkoutPlan::~WorkoutPlan() {

}

vector<Exercise>* WorkoutPlan::GetExercises() {
	return exercises_;
}

string WorkoutPlan::GetName() {
	return name_;
}

void WorkoutPlan::SetName(string name) {
	name_ = name;
}

void WorkoutPlan::SetExercises(vector<Exercise>* exercises) {
	exercises_ = exercises;
}

//Returns true if any exercise's name contains the string name, case insensitive
//		  false if not
bool WorkoutPlan::ContainsExercise(string name) {
	for (int i = 0; i < exercises_->size(); i++) {
		string lowercase = (*exercises_)[i].GetName();
		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (lowercase.find(name) != std::string::npos) {
			return true;
		}
	}
	return false;
}

void WorkoutPlan::AddExercise(Exercise ex) {
	(*exercises_).push_back(ex);
}