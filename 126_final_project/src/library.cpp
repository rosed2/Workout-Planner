

#include "library.h"
#include "workout_plan.h"
#include "exercise.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;

Library::Library(vector<WorkoutPlan>* workout_plans, vector<Exercise>* exercises) {
	workout_plans_ = workout_plans;
	all_exercises_ = exercises;
}

Library::Library() {

}

Library::~Library() {
}

//Finds the workout plans in the library whose name contains the given string
vector<WorkoutPlan> Library::SearchForPlanByName(string name) {
	vector<WorkoutPlan> to_return;

	for (int i = 0; i < workout_plans_->size(); i++) {
		string lowercase = (*workout_plans_)[i].GetName();

		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (lowercase.find(name) != std::string::npos) {
			to_return.push_back((*workout_plans_)[i]);
		}
	}
	return to_return;
}

//Finds the workout plans in the library that have an exercise with a given name
vector<WorkoutPlan> Library::SearchForPlanByExercise(string name) {
	vector<WorkoutPlan> to_return;
	for (int i = 0; i < workout_plans_->size(); i++) {
		if ((*workout_plans_)[i].ContainsExercise(name)) {
			to_return.push_back((*workout_plans_)[i]);
		}
	}
	return to_return;
}

void Library::AddWorkoutPlan(WorkoutPlan plan) {
	workout_plans_->push_back(plan);
}

vector<WorkoutPlan>* Library::GetWorkoutPlans() {
	return workout_plans_;
}

vector<Exercise>* Library::GetAllExercises() {
	return all_exercises_;
}

//Finds the exercises in the library whose name contains the given string
vector<Exercise> Library::SearchForExercisesByName(string name) {
	vector<Exercise> to_return;

	for (int i = 0; i < all_exercises_->size(); i++) {
		string lowercase = (*all_exercises_)[i].GetName();

		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (lowercase.find(name) != std::string::npos) {
			to_return.push_back((*all_exercises_)[i]);
		}

		
	}
	return to_return;
}


//Finds the exercises in the library that use a certain muscle group
vector<Exercise> Library::SearchForExercisesByMuscle(string name) {
	vector<Exercise> to_return;

	for (int i = 0; i < all_exercises_->size(); i++) {
		string lowercase = (*all_exercises_)[i].GetMuscle();

		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (lowercase.find(name) != std::string::npos) {
			to_return.push_back((*all_exercises_)[i]);
		}
	}
	return to_return;
}

//Finds the exercises in the library that use a certain piece of equipment
vector<Exercise> Library::SearchForExercisesByEquipment(string name) {
	vector<Exercise> to_return;

	for (int i = 0; i < all_exercises_->size(); i++) {
		string lowercase = (*all_exercises_)[i].GetEquipment();

		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (lowercase.find(name) != std::string::npos) {
			to_return.push_back((*all_exercises_)[i]);
		}
	}
	return to_return;
}

