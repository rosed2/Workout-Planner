

#pragma once
#include <string>
#include <vector>
#include "exercise.h"

class WorkoutPlan 
{
public:
	WorkoutPlan(std::string, std::vector<Exercise>);
	~WorkoutPlan();
	std::string GetName();
	std::vector<Exercise> GetExercises();
	void SetName(std::string);
	void SetExercises(std::vector<Exercise>);
	bool ContainsExercise(std::string);

private:
	std::string name_;
	std::vector<Exercise> exercises_;

};