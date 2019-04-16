

#include "workout_plan.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

WorkoutPlan::WorkoutPlan(string name, vector<Exercise> exercises) {
	name_ = name;
	exercises_ = exercises;
}

WorkoutPlan::~WorkoutPlan() {

}

vector<Exercise> WorkoutPlan::GetExercises() {
	return exercises_;
}

string WorkoutPlan::GetName() {
	return name_;
}

void WorkoutPlan::SetName(string name) {
	name_ = name;
}

void WorkoutPlan::SetExercises(vector<Exercise> exercises) {
	exercises_ = exercises;
}

bool WorkoutPlan::ContainsExercise(string exercise_name) {
	for (int i = 0; i < exercises_.size(); i++) {
		if (exercises_[i].GetName().find(exercise_name) != std::string::npos) {
			return true;
		}
	}
	return false;
}