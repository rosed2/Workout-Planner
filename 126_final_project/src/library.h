

#pragma once
#include <string>
#include <vector>
#include "exercise.h"
#include "workout_plan.h"

class Library
{
public:
	Library(std::vector<WorkoutPlan>);
	~Library();
	std::vector<WorkoutPlan> SearchForPlanByName(std::string);
	std::vector<WorkoutPlan> SearchForPlanByExercise(std::string);
	void AddWorkoutPlan(std::vector<WorkoutPlan>);

private:
	std::vector<WorkoutPlan> workout_plans_;
};