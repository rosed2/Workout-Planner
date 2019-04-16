

#include "library.h"
#include "workout_plan.h"
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;

Library::Library(vector<WorkoutPlan> workout_plans) {
	workout_plans_ = workout_plans;
}

Library::~Library() {
}

//Finds the workout plans in the library whose name contains the given string
vector<WorkoutPlan> Library::SearchForPlanByName(string name) {
	vector<WorkoutPlan> to_return;

	for (int i = 0; i < workout_plans_.size(); i++) {

		string lowercase = workout_plans_[i].GetName();
		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (lowercase.find(name) != std::string::npos) {
			to_return.push_back(workout_plans_[i]);
		}
	}
	return to_return;
}

//Finds the workout plans in the library that have an exercise with a given name
vector<WorkoutPlan> Library::SearchForPlanByExercise(string name) {
	vector<WorkoutPlan> to_return;
	for (int i = 0; i < workout_plans_.size(); i++) {
		if (workout_plans_[i].ContainsExercise(name)) {
			to_return.push_back(workout_plans_[i]);
		}
	}
	return to_return;
}

void Library::AddWorkoutPlan(WorkoutPlan plan) {
	workout_plans_.push_back(plan);
}

vector<WorkoutPlan> Library::GetWorkoutPlans() {
	return workout_plans_;
}